#pragma once

#include <raylib.h>
#include <string>
#include <cmath>

#include "map/mapMan.hpp"

enum Dir{
    DIR_RIGHT, DIR_DOWN, DIR_LEFT, DIR_UP
};

enum EnemyList{
    E_NULL, E_1, E_2
};

struct enemyStats{
    float maxHealth;
    float health;
    float speed;
};

class enemys{
private:
    enemyStats stats;
    float timeBackup = 0.f;
    Vector2 pos;
    const Texture2D* text;
    int endData = -1;
    bool active = true;
    int lastDir = -1;
    Vector2 direction = {0.f,0.f};
public:
    enemys(const Texture2D& text, Vector2 pos, enemyStats stats) : pos(pos), text(&text), stats(stats) {};
    ~enemys() = default;

    Rectangle getRec() const {return {pos.x, pos.y, (float)text->width, (float)text->height};};
    Vector2 getPos() const {return pos;};
    Vector2* getPosPtr() {return &pos;};

    enemyStats getStats() const {return stats;};
    bool getActive() const {return active;};
    int getEndData() const {return endData;};

    void kill() {active=0;};

    void attack(float attack) {
        if(stats.health-attack <= 0){
            active = 0;
            pos = {-9999, -9999};
        } else {
            stats.health-=attack;
        }
    };

    void aiLoop(mapMan& man, const float dt);
    void move(float dt);
    void draw();
};
