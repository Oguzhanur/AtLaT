#pragma once

#include <raylib.h>
#include <string>
#include <format>

class healthBar{
private:
    float maxHealth;
    Vector2 pos;
    Vector2 size;
    float gap;
    std::string baseText;
    bool active;
public:
    healthBar(Vector2 pos, Vector2 size, float gap, float maxHealth, std::string baseText, bool active) 
        : maxHealth(maxHealth), pos(pos), size(size), baseText(baseText), active(active), gap(gap) {}
    ~healthBar() = default;

    Vector2 getSize() const {return size;};
    Vector2 getPos() const {return pos;};
    float getMaxHealth() const {return maxHealth;};

    void setPos(Vector2 newPos) {pos=newPos;};
    void setMaxHealth(int newMaxHealth) {maxHealth = newMaxHealth;};
    void setActive(bool newA) {active = newA;};

    std::string getAsText(float health) {
        return  baseText + std::to_string(static_cast<int>(health)) + "/" + std::to_string(static_cast<int>(maxHealth));
    }

    void draw(float health);
};
