#pragma once
#include <raylib.h>
#include <string>
#include <memory>
#include "towers/bullet.hpp"

enum TowerType{
    T_NOTOWER, 
    T_TOWER1, 
    T_TOWER2, 
    T_TOWER3, 
    T_TOWER4,
    T_TOWER5
};

struct towerStats{
    float damage;
    float range;
    float attackSpeed;
    int cost;
};

class tower1{
private:
    Vector2 pos{};
    const Texture2D* text;
    towerStats stats;
    int type;
    float dataBackup=0.f;
public:
    tower1(const Texture2D& text, Vector2 pos, towerStats stats, int type) : pos(pos), text(&text), stats(stats), type(type) {};
    ~tower1() = default;

    Vector2 getPos() const {return pos;};
    Vector2 getCenter() {return {pos.x+16, pos.y+16};};
    towerStats getStats() const {return stats;};
    int getType() const {return type;};

    bool getBulletIsReady(float dt) {return dataBackup+stats.attackSpeed<=dt;};
    void setTimer(float dt) {dataBackup = dt;};

    void draw();
    void drawEx(Vector2 pos);
};
