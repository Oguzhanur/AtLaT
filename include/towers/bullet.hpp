#pragma once
#include <raylib.h>
#include <raymath.h>
#include "enemy/enemys.hpp"

class Bullet{
private:
    float damage;
    Vector2 pos;
    Vector2* target;
    Color bColor = RED;
    int lifeTime = 200;
    float speed = 12.0f;
    bool active = true;
public:
    Bullet(Vector2 pos, Vector2* target, float speed, float damage) : pos(pos), target(target), speed(speed), damage(damage) {}
    ~Bullet() = default;

    Vector2 getPos() const {return pos;};
    bool getActive() const {return active;};
    bool getDamage() const {return damage;};
    bool getSpeed() const {return speed;};

    void killBullet() {active=0;};

    void updateBullet(float dt);
    void draw();
};