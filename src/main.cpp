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
#include "screens/demoEndScreen.hpp"

int main(void) {
    ctx GData;

    TraceLog(LOG_INFO, "MAIN BASLADI");
    InitWindow(GData.ScreenSize.x, GData.ScreenSize.y, "Tank Oyunu");
    InitAudioDevice();
    SetTargetFPS(60);

    // EKRANLAR
    baseScreen* currentScreen = nullptr;

    // Loop
    while (!WindowShouldClose() && GData.status!= SCREEN_CLOSE){
        // Tam ekran
        if(GData.fullscreen){
            SetWindowState(FLAG_FULLSCREEN_MODE);
        } else {
            ClearWindowState(FLAG_FULLSCREEN_MODE);
        }

        // Ekran değişimi
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
                case SCREEN_DEMOEND:
                    currentScreen = new demoendScreen(&GData);
                    break;
                case SCREEN_CLOSE:
                    CloseAudioDevice();
                    CloseWindow();
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

    CloseAudioDevice();
    CloseWindow();
    return 0;
}