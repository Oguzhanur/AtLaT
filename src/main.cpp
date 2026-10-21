#include <raylib.h>
#include <vector>
#include <ostream>
#include <algorithm>
#include <cmath>
#include <format>

#include "core/ctx.hpp"

#include "map/mapMan.hpp"
#include "gui/buttons.hpp"
#include "gui/textures.hpp"
#include "gui/healthBar.hpp"
#include "gui/text.hpp"

#include "towers/towers.hpp"
#include "enemy/enemys.hpp"

#include "enemy/wawe.hpp"


int main(void) {
    ctx GData;

    TraceLog(LOG_INFO, "MAIN BASLADI");
    InitWindow(GData.ScreenSize.x, GData.ScreenSize.y, "Tank Oyunu");

    SetTargetFPS(60);

    mapMan mapMan1;

    // Base
    int money = 300;
    float baseHealth = 100.f;
    healthBar hBar({20,20}, {400,50}, baseHealth);

    // Kamera
    Camera2D camera = { 0 };
    camera.target = {GData.ScreenSize.x/2, GData.ScreenSize.y/2};
    camera.offset = {GData.ScreenSize.x/2, GData.ScreenSize.y/2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Selected
    float frameTime = 0.f;
    float TimeAsFrame = 0.f;
    int selectedBut = 0;

    Color BColor{0,100,0,100};

    // Arayüz

    gui::texture texture1("data/gui/LMenu.png", {1000,0});


    gui::font mainFont("data/font/Bungee-Regular.ttf", 32.f);

    // Kule 1
    float tower1Cost = 150.f;
    gui::button tower1button("data/gui/item1But.png", {1100,0});
    gui::texture tower1Tower("data/gui/item1.png", {0,0});
    Texture2D tower1Text = LoadTexture("data/gui/item1.png");

    Texture2D enemy1Text = LoadTexture("data/enemy.png");

    std::vector<tower1> placedTowers;
    std::vector<enemys> enemysComming;
    std::vector<Bullet> bullets;

    // Wawe
    std::vector<wawe> wawes{ // Geleceği frame / Kule / Sayısı
        {1   , T_TOWER1, 100},
        {2   , T_TOWER1, 1},
        {4   , T_TOWER1, 1},
        {5.0 , T_TOWER1, 7},
        {6.5 , T_TOWER1, 9},
        {7.8 , T_TOWER1, 12},
        {9.2 , T_TOWER1, 15},
        {11.4, T_TOWER1, 18},
        {11.8, T_TOWER1, 32},
        {12.1, T_TOWER1, 64},
        {12.5, T_TOWER1, 98},
        {12.9, T_TOWER1, 120},
        {13.8, T_TOWER1, 138},
    };

    // Ana loop
    while (!WindowShouldClose()){
        frameTime = GetFrameTime();
        TimeAsFrame += frameTime;
        // Kamera hareketleri
        if(IsKeyDown(KEY_Q) && camera.zoom < 2.f){
            camera.zoom += 0.01f;
        } else if (IsKeyDown(KEY_E) && camera.zoom > 0.1f) {
            camera.zoom -= 0.01f;
        }

        if (IsKeyDown(KEY_W)){
            camera.target.y += -5;
        } else if (IsKeyDown(KEY_S)){
            camera.target.y +=  5;
        } if (IsKeyDown(KEY_A)){
            camera.target.x += -5;
        } else if (IsKeyDown(KEY_D)){
            camera.target.x +=  5;
        }

        // Ai ve arka sistemler
        for (enemys& enemy : enemysComming){
            enemy.aiLoop(mapMan1);
            enemy.move(frameTime);
                    
            if(enemy.getEndData()==1){
                baseHealth-=enemy.getHealth();
                enemy.kill();
            }
        }


        for (Bullet& bul : bullets){
            if(bul.getActive()){ 
                bul.updateBullet(frameTime);

                for (enemys& enemy : enemysComming){
                    if (CheckCollisionPointCircle(enemy.getPos(), bul.getPos(), 32) && enemy.getActive()){
                        bul.killBullet();
                        enemy.attack(bul.getDamage());
                        money += bul.getDamage();

                        break;
                    }
                }
            }
        }


        for (tower1& tower : placedTowers){
            if(!tower.getBulletIsReady(TimeAsFrame)) continue;

            for (enemys& enemy : enemysComming){
                if (!enemy.getActive()) continue;

                if(CheckCollisionCircleRec(tower.getCenter(), tower.getRange(), enemy.getRec())){
                    bullets.push_back(Bullet{tower.getCenter(), enemy.getPosPtr(), 2500.f, tower.getDamage()});
                    tower.setTimer(TimeAsFrame);
                    break;
                }
            }
        }

        // Wawe'ler
        for (wawe& w : wawes){
            if(w.getActive() && std::abs(w.getTimeAsFrame()-TimeAsFrame)<=0.1){
                enemysComming.emplace_back(enemy1Text, Vector2{0, 192}, 128.f);
                w.countN();
            }
        }

        // Temizlik
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {return !bullet.getActive();}), bullets.end()
        );
        enemysComming.erase(
            std::remove_if(enemysComming.begin(), enemysComming.end(), [](const enemys& enemy) {return !enemy.getActive();}), enemysComming.end()
        );

        // Çizimler
        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

                mapMan1.draw();

                if(selectedBut==1){
                    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                    Vector2 newPos = { worldPos.x-tower1Tower.getSize().x/2, 
                                       worldPos.y-tower1Tower.getSize().y/2 };
                    tower1Tower.drawEx(newPos, 1.f);
                }

                for (tower1& tower : placedTowers){
                    tower.draw();
                    DrawCircleV(tower.getCenter(), tower.getRange(), BColor);}

                for (Bullet& bul : bullets){
                    if (bul.getActive()) bul.draw();}

                for (enemys& enemy : enemysComming){ 
                    if (enemy.getActive()) enemy.draw();}

            EndMode2D();

            texture1.draw();
            tower1button.draw();
            hBar.draw(baseHealth);

            Vector2 hPos = hBar.getPos();
            Vector2 hSize = hBar.getSize();

            gui::drawText(hBar.getAsText(baseHealth), {hPos.x, hPos.y+hSize.y+10}, mainFont, WHITE);

            std::string moneyText = "Money: " + std::to_string(money);
            gui::drawText(moneyText, {1000-200,20}, mainFont, Color{255,215,0,255});

        EndDrawing();
        
        
        Vector2 mousePos = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            if(selectedBut!=0){
                Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                TileData data = mapMan1.getTileByPos(worldPos);

                if(data.type==1){
                    for (tower1& tower : placedTowers){
                        if(mapMan1.getRealPos(data.tilePos).x == tower.getPos().x && mapMan1.getRealPos(data.tilePos).y == tower.getPos().y) data.isTileEmpty = 0;
                    }
                    if(data.isTileEmpty && tower1Cost<=money){
                        placedTowers.emplace_back(tower1Text, mapMan1.getRealPos(data.tilePos));
                        selectedBut = 0;
                        money -= tower1Cost;
                    }
                }
            }

            if(tower1button.isClicked(mousePos)){
                if(selectedBut==1){
                    selectedBut = 0;
                } else {
                    selectedBut = 1;
                }
            }
        }
    }
    
    CloseWindow();
    return 0;
}