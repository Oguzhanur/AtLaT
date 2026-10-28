#pragma once

#include <raylib.h>
#include <string>

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

    int status;
};