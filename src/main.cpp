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

    // Kuleler
    std::vector<int> tList = {1,2};

    // Kuleler
    std::vector<towerStats> TStats = { //? Hasar, Alan, Saldırı Hızı, Maliyet
        {5.f, 150.f, 0.5f, 150},
        {25.f, 300.f, 2.0f, 200}
    };

    std::vector<gui::button> towerButtons;

    std::vector<Texture2D> towerTextures;
    std::vector<Texture2D> towerBulletTextures;

    // Kule 1
    Texture2D tower1BText = LoadTexture("data/items/item1But.png");
    towerTextures.push_back(LoadTexture("data/items/item1.png"));
    towerBulletTextures.push_back(LoadTexture("data/items/item1Bul.png"));

    towerButtons.push_back(gui::button{tower1BText, {1100,0}});


    // Kule 2
    Texture2D tower2BText = LoadTexture("data/items/item2But.png");
    towerButtons.emplace_back(gui::button{tower2BText, {1000,0}});

    towerTextures.push_back(LoadTexture("data/items/item2.png"));
    towerBulletTextures.push_back(LoadTexture("data/items/item2Bul.png"));

    //gui::texture tower2Tower("data/items/item2.png", {0,0});



    // Düşmanlar
    Texture2D enemy1Text = LoadTexture("data/enemy.png");

    std::vector<tower1> placedTowers;
    std::vector<enemys> enemysComming;
    std::vector<Bullet> bullets;

    // Wawe
    std::vector<wawe> wawes{ // Geleceği frame / Kule / Sayısı / Aralık
        {1  , E_1, 30, 1},
        {20 , E_1, 50, 0.5},
        {45 , E_1, 10, 1},
        {60 , E_1, 100, 0.01}
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
            enemy.aiLoop(mapMan1, frameTime);
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

                const towerStats& stats = tower.getStats();
                if(CheckCollisionCircleRec(tower.getCenter(), stats.range, enemy.getRec())){
                    bullets.push_back(Bullet{towerBulletTextures[tower.getType()-1], tower.getCenter(), enemy.getPosPtr(), 1500.f, stats.damage});
                    tower.setTimer(TimeAsFrame);
                    break;
                }
            }
        }

        // Wawe'ler
        for (wawe& w : wawes){
            if(w.getActive() && TimeAsFrame>+w.getSavedClock()+w.getInterval() && TimeAsFrame > w.getTimeAsFrame()){
                w.saveTime(TimeAsFrame);
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

                if(selectedBut>0 && selectedBut-1 < towerTextures.size()){
                    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                    Vector2 newPos = { worldPos.x-towerTextures[selectedBut-1].width/2, 
                                       worldPos.y-towerTextures[selectedBut-1].height/2 };
                    DrawTextureEx(towerTextures[selectedBut-1], newPos, 0.f, 1.f, WHITE);
                    
                }

                for (tower1& tower : placedTowers){
                    tower.draw();
                    DrawCircleV(tower.getCenter(), tower.getStats().range, BColor);}

                for (Bullet& bul : bullets){
                    if (bul.getActive()) bul.draw();}

                for (enemys& enemy : enemysComming){ 
                    if (enemy.getActive()) enemy.draw();}

            EndMode2D();

            texture1.draw();
            for(int x=1; x<=towerButtons.size(); x++){
                towerButtons[x-1].draw();
            }


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

                if(data.type>0){
                    for (tower1& tower : placedTowers){
                        if(mapMan1.getRealPos(data.tilePos).x == tower.getPos().x && mapMan1.getRealPos(data.tilePos).y == tower.getPos().y) data.isTileEmpty = 0;
                    }

                    if(data.isTileEmpty && TStats[selectedBut-1].cost<=money){
                        placedTowers.emplace_back(towerTextures[selectedBut-1], mapMan1.getRealPos(data.tilePos), TStats[selectedBut-1], selectedBut);
                        money -= TStats[selectedBut-1].cost;
                        selectedBut = 0;
                    }
                }
            }

            for(int x=1; x<=towerButtons.size(); x++){
                if(towerButtons[x-1].isClicked(mousePos)){
                    if(selectedBut==x){
                        selectedBut = 0;
                    } else {
                        selectedBut = x;
                    }
                }
            }
        }
    }
    
    CloseWindow();
    return 0;
}