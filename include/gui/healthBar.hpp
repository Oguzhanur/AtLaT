#pragma once

#include <raylib.h>
#include <string>

class healthBar{
private:
    float maxHealth;
    Vector2 pos;
    Vector2 size;
public:
    healthBar(Vector2 pos, Vector2 size, float maxHealth) : maxHealth(maxHealth), pos(pos), size(size) {}
    ~healthBar() = default;

    void draw(float health);
};
