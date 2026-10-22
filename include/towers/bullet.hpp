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
    const Texture2D* text;
    int lifeTime = 200;
    float speed = 12.0f;
    bool active = true;
public:
    Bullet(const Texture2D& text, Vector2 pos, Vector2* target, float speed, float damage) : pos(pos), target(target), speed(speed), damage(damage), text(&text) {}
    ~Bullet() = default;

    Vector2 getPos() const {return pos;};
    bool getActive() const {return active;};
    float getDamage() const {return damage;};
    bool getSpeed() const {return speed;};

    void killBullet() {active=0;};

    void updateBullet(float dt);
    void draw();
};