#pragma once

#include <raylib.h>
#include <string>
#include <format>

class healthBar{
private:
    float maxHealth;
    Vector2 pos;
    Vector2 size;
public:
    healthBar(Vector2 pos, Vector2 size, float maxHealth) : maxHealth(maxHealth), pos(pos), size(size) {}
    ~healthBar() = default;

    Vector2 getSize() const {return size;};
    Vector2 getPos() const {return pos;};
    float getMaxHealth() const {return maxHealth;};

    std::string getAsText(float health) {
        return  "Health: " + std::to_string(static_cast<int>(health)) + "/" + std::to_string(static_cast<int>(maxHealth));
    }

    void draw(float health);
};
