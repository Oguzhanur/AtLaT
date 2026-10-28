#pragma once
#include <raylib.h>
#include <raymath.h>
#include "towers/towers.hpp"

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

    std::vector<int> specials;
public:
    Bullet(const Texture2D& text, Vector2 pos, Vector2* target, float speed, float damage, std::vector<int> specials) 
        : pos(pos), target(target), speed(speed), damage(damage), text(&text), specials(specials) {}
    ~Bullet() = default;

    Vector2 getPos() const {return pos;};
    bool getActive() const {return active;};
    float getDamage() const {return damage;};
    bool getSpeed() const {return speed;};
    std::vector<int> getSpecials() const {return specials;};

    const Texture2D* getText() const {return text;};

    void killBullet() {active=0;};

    void updateBullet(float dt);
    void draw();
};