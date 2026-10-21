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
    float damage=10.f;
    float range=150.f;
    float attackSpeed=0.1f;
    float dataBackup=0.f;
public:
    tower1(const Texture2D& text, Vector2 pos) : pos(pos), text(&text) {};
    ~tower1() = default;

    Vector2 getPos() const {return pos;};
    float getRange() const {return range;};
    Vector2 getCenter() {return {pos.x+16, pos.y+16};};
    float getDamage() const {return damage;};

    bool getBulletIsReady(float dt) {return dataBackup+attackSpeed<=dt;};
    void setTimer(float dt) {dataBackup = dt;};

    void draw();
    void drawEx(Vector2 pos);
};
