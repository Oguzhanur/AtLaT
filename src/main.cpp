#include <raylib.h>
#include <vector>
#include <ostream>
#include <algorithm>

#include "core/ctx.hpp"

#include "map/mapMan.hpp"
#include "gui/buttons.hpp"
#include "gui/textures.hpp"
#include "towers/towers.hpp"
#include "enemy/enemys.hpp"


int main(void) {
    ctx GData;

    TraceLog(LOG_INFO, "MAIN BASLADI");
    InitWindow(GData.ScreenSize.x, GData.ScreenSize.y, "Tank Oyunu");

    SetTargetFPS(60);

    mapMan mapMan1;

    // Kamera
    Camera2D camera = { 0 };
    camera.target = {GData.ScreenSize.x/2, GData.ScreenSize.y/2};
    camera.offset = {GData.ScreenSize.x/2, GData.ScreenSize.y/2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Selected
    int selectedBut = 0;

    Color BColor{0,100,0,100};

    // Button
    gui::button buton1("data/gui/but1.png", {1100,0});

    gui::texture texture1("data/gui/LMenu.png", {1000,0});

    gui::texture mainTower("data/gui/item1.png", {0,0});

    Texture2D tower1Text = LoadTexture("data/gui/item1.png");
    Texture2D enemy1Text = LoadTexture("data/enemy.png");

    std::vector<tower1> placedTowers;
    std::vector<enemys> enemysComming;
    std::vector<Bullet> bullets;

    enemysComming.emplace_back(enemy1Text, Vector2{-32, 96});

    enemysComming.emplace_back(enemy1Text, Vector2{0, 96});

    // Ana loop
    while (!WindowShouldClose()){
        float dt = GetFrameTime();
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

        // Çizimler
        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

                mapMan1.draw();


                if(selectedBut==1){
                    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                    Vector2 newPos = { worldPos.x-mainTower.getSize().x/2, 
                                       worldPos.y-mainTower.getSize().y/2 };
                    mainTower.drawEx(newPos, 1.f);
                }

                for (tower1& tower : placedTowers){
                    tower.draw();
                    //TraceLog(LOG_INFO, "TowerDraww: %i: {%f, %f}", tower.getTexture()->id, tower.getPos().x, tower.getPos().y);
                    DrawCircleV(tower.getCenter(), tower.getRange(), BColor);

                    for (enemys& enemy : enemysComming){
                        if(CheckCollisionCircleRec(tower.getCenter(), tower.getRange(), enemy.getRec())){
                            bullets.push_back(Bullet{tower.getCenter(), enemy.getPosPtr(), 25.f});

                            break;
                        }
                    }
                }

                for (Bullet& bul : bullets){
                    if(bul.getActive()){ 
                        bul.updateBullet(dt);

                        bul.draw();

                        for (enemys& enemy : enemysComming){
                            if (CheckCollisionPointCircle(enemy.getPos(), bul.getPos(), 3.0f) && enemy.getActive()){
                                bul.killBullet();
                                enemy.attack(bul.getDamage());
                            }
                        }
                    }
                }

                bullets.erase(
                    std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {return !bullet.getActive();}), bullets.end()
                );
                enemysComming.erase(
                    std::remove_if(enemysComming.begin(), enemysComming.end(), [](const enemys& enemy) {return !enemy.getActive();}), enemysComming.end()
                );

                for (enemys& enemy : enemysComming){
                    enemy.draw();

                    enemy.aiLoop(mapMan1);
                    enemy.move(dt);
                }


            EndMode2D();

            texture1.draw();
            buton1.draw();

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
                    if(data.isTileEmpty){
                        TraceLog(LOG_INFO, "BLOK KOYULDU");
                        placedTowers.emplace_back(tower1Text, mapMan1.getRealPos(data.tilePos));
                        selectedBut = 0;
                    }
                }
            }

            if(buton1.isClicked(mousePos)){
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