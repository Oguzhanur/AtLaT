#pragma once

#include <raylib.h>
#include <string>
#include <vector>

inline float NULL_POS = -999;

enum Screens{
    SCREEN_NULL,

    SCREEN_MAINMENU,
    SCREEN_GAMEPLAY,
    SCREEN_SETTINGS,
    SCREEN_GAMESELECT,
    SCREEN_END
};

enum Hardness{
    H_NULL,
    H_HARD,
    H_NORMAL,
    H_EASY,
};

struct Vector2i{
    int x;
    int y;

    bool operator==(const Vector2i& other) const {
        return x == other.x &&
               y == other.y;
    }
};

enum TowerType{
    T_NOTOWER, 
    T_NORMAL, 
    T_RANGE, 
    T_TOWER3, 
    T_TOWER4,
    T_TOWER5
};

struct ctx{
    Vector2 ScreenSize = {1280,720};
    float gameSpeed = 1.f; //TODO: uygulanabilir gameSpeed yap

    bool debugMode = 1;
    int status = SCREEN_GAMEPLAY;
    int hardness = H_NORMAL;

    std::vector<int> havedTowerList = {0,1};
    int curentWawe = 1;
    int endedWawes = 0;

    //? Screen'lar arası iletişim
    int isPlayerWinnedGame = -1;
};