#include "towers/bullet.hpp"

void Bullet::updateBullet(float dt){
    if (target->x == -9999 && target->y == -9999) {
        active = false;
        return;
    }

    Vector2 direction = Vector2Subtract(*target, pos);
    float distance = Vector2Length(direction);

    if (distance <= speed * dt) {
        active = false;
        return;
    }

    direction = Vector2Normalize(direction);
    pos = Vector2Add(pos, Vector2Scale(direction, speed * dt));
}

void Bullet::draw(){
    if(active) DrawRectangleV(pos, {10,10}, bColor);
}