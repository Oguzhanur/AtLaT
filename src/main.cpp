#include <raylib.h>
#include <vector>
#include <ostream>
#include <algorithm>
#include <cmath>
#include <format>

#include "screens/gameplay.hpp"
#include "screens/mainMenu.hpp"
#include "screens/endScreen.hpp"
#include "screens/settings.hpp"
#include "screens/gameselect.hpp"

int main(void) {
    ctx GData;

    TraceLog(LOG_INFO, "MAIN BASLADI");
    InitWindow(GData.ScreenSize.x, GData.ScreenSize.y, "Tank Oyunu");

    SetTargetFPS(60);

    // EKRANLAR
    baseScreen* currentScreen = nullptr;

    // Loop
    while (!WindowShouldClose()){
        if(GData.status!=SCREEN_NULL){
            delete currentScreen;

            switch (GData.status){
                case SCREEN_MAINMENU:
                    currentScreen = new mainMenuScreen(&GData);
                    break;
                case SCREEN_GAMEPLAY:
                    currentScreen = new gameplayScreen(&GData);
                    break;
                case SCREEN_SETTINGS:
                    currentScreen = new settingsScreen(&GData);
                    break;
                case SCREEN_GAMESELECT:
                    currentScreen = new gameselectScreen(&GData);
                    break;
                case SCREEN_END:
                    currentScreen = new endScreen(&GData);
                    break;

            }
            
            currentScreen->start();
            GData.status = SCREEN_NULL;
        }

        BeginDrawing();
            currentScreen->draw();
        EndDrawing();
        currentScreen->loop();
    }

    CloseWindow();
    return 0;
}