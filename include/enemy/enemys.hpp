#pragma once

#include <raylib.h>
#include <string>

#include "map/mapMan.hpp"

enum Dir{
    DIR_NONE, DIR_LEFT, DIR_RIGHT, DIR_UP, DIR_DOWN
};

class enemys{
private:
    Vector2 pos;
    Texture2D text;
    int lastDir = 0;
    Vector2 direction = {0.f,0.f};
    float speed = 8.f;
public:
    enemys(const std::string& path, Vector2 pos);
    ~enemys();
    void aiLoop(mapMan& man);
    void move();
    void draw();
};
