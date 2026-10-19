#include "towers/bullet.hpp"

void Bullet::updateBullet(float dt){
    dt=1.f; //! dt ile işlevsel çalışsın ve bunu kaldır.
    Vector2 direction = Vector2Subtract(*target, pos);
    direction = Vector2Normalize(direction);

    pos = Vector2Add(pos, Vector2Scale(direction, speed * dt));

    if(target->x == -9999 && target->y == -9999) {
        bColor = Color{0,0,0,0};
        active = 0;
    };
}

void Bullet::draw(){
    if(active) DrawRectangleV(pos, {10,10}, bColor);
}