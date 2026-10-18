#pragma once
#include <raylib.h>
#include <raymath.h>
class Bullet{
private:
    Vector2 pos;
    Vector2 target;
    float speed = 2.0f;
    bool active = true;
public:
    Bullet(Vector2 pos, Vector2 target, float speed) : pos(pos), target(target), speed(speed) {}
    ~Bullet() = default;

    Vector2 getPos() const {return pos;};
    bool getActive() const {return active;};

    void updateBullet(float dt);
    void draw();
};