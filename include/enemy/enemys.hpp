#pragma once

#include <raylib.h>
#include <string>

#include "map/mapMan.hpp"

enum Dir{
    DIR_RIGHT, DIR_DOWN, DIR_LEFT, DIR_UP
};

class enemys{
private:
    Vector2 pos;
    Texture2D text;
    int lastDir = -1;
    Vector2 direction = {0.f,0.f};
    float speed = 4.f ;
public:
    enemys(const std::string& path, Vector2 pos);
    ~enemys();

    Rectangle getRec() {return {pos.x, pos.y, (float)text.width, (float)text.height};};
    Vector2 getPos() {return pos;};

    void aiLoop(mapMan& man);
    void move(float dt);
    void draw();
};
