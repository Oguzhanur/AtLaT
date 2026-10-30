#pragma once

#include <raylib.h>
#include <string>

inline float NULL_POS = -999;

enum Screens{
    SCREEN_NULL,

    SCREEN_MAINMENU,
    SCREEN_GAMEPLAY,
    SCREEN_GAMEMENU,

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


struct ctx{
    Vector2 ScreenSize = {1200,800};
    float gameSpeed = 1.f; //TODO: uygulanabilir gameSpeed yap

    int status = 1;
    int hardness = H_NORMAL;

    //? Screen'lar arası iletişim
    int isPlayerWinnedGame = 0;
};