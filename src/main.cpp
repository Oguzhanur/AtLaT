#include <raylib.h>
#include <vector>
#include <ostream>

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
    bool towerOn = false;
    int selectedBut = 0;

    Color BColor{0,100,0,100};

    // Button
    gui::button buton1("data/gui/but1.png", {1100,0});

    gui::texture texture1("data/gui/LMenu.png", {1000,0});

    gui::texture mainTower("data/gui/item1.png", {0,0});

    Texture2D tower1Text = LoadTexture("data/gui/item1.png");
    enemys enemy1("data/enemy.png", {-32,96});

    std::vector<tower1> placedTowers;

    // Ana loop
    while (!WindowShouldClose()){
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
                }

                enemy1.draw();

            EndMode2D();

            texture1.draw();
            buton1.draw();

        EndDrawing();
        
        enemy1.aiLoop(mapMan1);
        enemy1.move();

        for (tower1& tower : placedTowers){
            Vector2 center = {tower.getPos().x + tower.getRange(), tower.getPos().y + tower.getRange()};
            if(CheckCollisionCircleRec(tower.getCenter(), tower.getRange(), enemy1.getRec())){
                TraceLog(LOG_INFO, "HEDEF VAR!!!");
                //tower.createBullet(center, enemy1.getPos());
                BColor = {100,0,0,100};
            } else {
                BColor = {0,100,0,100};
            }
        }

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