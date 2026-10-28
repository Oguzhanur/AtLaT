#include <raylib.h>
#include <vector>
#include <ostream>
#include <algorithm>
#include <cmath>
#include <format>

#include "screens/base.hpp"
#include "screens/gameplay.hpp"

int main(void) {
    ctx GData;

    TraceLog(LOG_INFO, "MAIN BASLADI");
    InitWindow(GData.ScreenSize.x, GData.ScreenSize.y, "Tank Oyunu");

    SetTargetFPS(60);

    // EKRANLAR
    baseScreen* currentScreen = new gameplayScreen(&GData);
    currentScreen->start();

    // Loop
    while (!WindowShouldClose()){
        currentScreen->loop();
        currentScreen->draw();
    }

    CloseWindow();
    return 0;
}