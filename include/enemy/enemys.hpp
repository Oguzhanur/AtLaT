#pragma once

#include <raylib.h>
#include <string>

#include "map/mapMan.hpp"

enum Dir{
    DIR_RIGHT, DIR_DOWN, DIR_LEFT, DIR_UP
};

class enemys{
private:
    float maxHealth = 100.f;
    float health = 100.f;
    Vector2 pos;
    const Texture2D* text;
    bool active = true;
    int lastDir = -1;
    Vector2 direction = {0.f,0.f};
    float speed = 4.f ;
public:
    enemys(const Texture2D& text, Vector2 pos) : pos(pos), text(&text) {};
    ~enemys() = default;

    Rectangle getRec() const {return {pos.x, pos.y, (float)text->width, (float)text->height};};
    Vector2 getPos() const {return pos;};
    Vector2* getPosPtr() {return &pos;};

    float getHealth() const {return health;};
    float getMaxHealth() const {return maxHealth;};
    bool getActive() const {return active;};

    void killBullet() {active=0;};

    void attack(float attack) {
        if(health-attack <= 0){
            active = false;
            pos = {-9999, -9999};
        } else {
            health-=attack;
        }
    };

    void aiLoop(mapMan& man);
    void move(float dt);
    void draw();
};
