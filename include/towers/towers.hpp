#pragma once
#include <raylib.h>
#include <string>
#include <memory>
#include "towers/bullet.hpp"

enum TowerType{
    T_NOTOWER, T_TOWER1, T_TOWER2, T_TOWER3, T_TOWER4, T_TOWER5,
};

class tower1{
private:
    Vector2 pos{};
    const Texture2D* text;
    float range=150.f;
public:
    tower1(const Texture2D& text, Vector2 pos) : pos(pos), text(&text) {};
    ~tower1() = default;

    Vector2 getPos() {return pos;};
    float getRange() {return range;};
    Vector2 getCenter() {return {pos.x+16, pos.y+16};};

    void draw();
    void drawEx(Vector2 pos);
};
