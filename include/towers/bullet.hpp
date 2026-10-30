#pragma once
#include <raylib.h>
#include <raymath.h>
#include <vector>
#include "towers/towerSpecial.hpp"

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

    int specialCount;
    std::vector<TowerSpecial> specials;
public:
    Bullet(const Texture2D& text, Vector2 pos, Vector2* target, float speed, float damage, std::vector<TowerSpecial> specials) 
        : pos(pos), target(target), speed(speed), damage(damage), text(&text), specials(specials) {}
    ~Bullet() = default;

    Vector2 getPos() const {return pos;};
    bool getActive() const {return active;};
    float getDamage() const {return damage;};
    bool getSpeed() const {return speed;};
    std::vector<TowerSpecial> getSpecials() const {return specials;};

    const Texture2D* getText() const {return text;};

    void killBullet() {active=0;};

    void updateBullet(float dt);
    void draw();
};