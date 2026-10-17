#include <raylib.h>
#include <iostream>

#include "core/ctx.hpp"

#include "core/cute_tiled.h"
#include "map/mapMan.hpp"
#include "gui/buttons.hpp"
#include "gui/textures.hpp"

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

    // Button
    gui::button buton1("data/gui/but1.png", {1100,0});

    gui::texture texture1("data/gui/LMenu.png", {1000,0});
    gui::texture select1("data/gui/item1.png", {1000,0});

    bool placed = false;
    Vector2i placedPos;

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


                if(selectedBut!=0){
                    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                    Vector2 newPos = { worldPos.x-select1.getTexture().height/2, 
                                       worldPos.y-select1.getTexture().width/2 };
                    select1.drawEx(newPos, camera.zoom);
                }

                if(placed){
                    TraceLog(LOG_INFO, "TRUEEE");
                    select1.drawEx(mapMan1.getRealPos(placedPos), camera.zoom);
                }

            EndMode2D();

            texture1.draw();
            buton1.draw();


        EndDrawing();

        Vector2 mousePos = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && selectedBut!=0){
            TraceLog(LOG_INFO, "Koyuldu");
            Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            TileData data = mapMan1.getTileByPos(worldPos);
            if (data.trueVal) std::cout << data.type << ": " << data.tilePos.x << "," << data.tilePos.y << std::endl;

            placed = 1;
            TraceLog(LOG_INFO, "Veri : %d", placed);
            placedPos = data.tilePos;
            selectedBut = 0;
        }

        if(buton1.isClicked(mousePos) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            TraceLog(LOG_INFO, "buton1");
            if(selectedBut==1){
                selectedBut = 0;
            } else {
                selectedBut = 1;
            }
        }
    }

    
    CloseWindow();
    return 0;
}