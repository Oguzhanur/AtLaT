#include "towers/bullet.hpp"

void Bullet::updateBullet(float dt){
    dt=1.f; //! dt ile işlevsel çalışsın ve bunu kaldır.
    Vector2 direction = Vector2Subtract(target, pos);
    direction = Vector2Normalize(direction);

    pos = Vector2Add(pos, Vector2Scale(direction, speed * dt));

    if (CheckCollisionPointCircle(target, pos, 32.0f)){
        TraceLog(LOG_INFO, "Kapandı");
        active = false;
    }
}

void Bullet::draw(){
    TraceLog(LOG_INFO, "DRAW POS: %i {%f, %f}", active, pos.x, pos.y);
    if(active) DrawRectangleV(pos, {10,10}, RED);
}