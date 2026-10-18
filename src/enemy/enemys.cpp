#include "enemy/enemys.hpp"

enemys::enemys(const std::string& path, Vector2 pos) : pos(pos){
    text = LoadTexture(path.c_str());
}

enemys::~enemys(){
    UnloadTexture(text);
}

void enemys::aiLoop(mapMan& man){
    if(direction.x == 0 && direction.y == 0){
        Vector2 newPos = pos;
        float movementSpeed = 32;
        int size = 0;

        newPos.x+=size+movementSpeed;

        if (man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 1) && lastDir != DIR_LEFT && !man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 2)){
            //* ------- SAĞ -------
            direction.x = movementSpeed;
        } else {
            //* ------- SOL -------
            newPos.x-=size+movementSpeed*2;
            if(man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 1) && lastDir != DIR_RIGHT && !man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 2)){
                direction.x = -movementSpeed;
            } else {
                newPos.x = pos.x;
                newPos.y += size+movementSpeed;
                if(man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 1) && lastDir != DIR_UP && !man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 2)){
                    //* ------- AŞŞAĞI -------
                    direction.y = movementSpeed;
                } else {
                    //* ------- YUKARI -------
                    newPos.y -= size+movementSpeed*2;
                    if(man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 1) && lastDir != DIR_DOWN && !man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 2)){
                        direction.y = -movementSpeed;
                    } else {
                        //* ------- HAREKET YOKKK -------
                        direction = {0,0};
                    }
                }
            }
        }
    }
}

void enemys::move(float dt){
    dt=1.f; //! dt ile işlevsel çalışsın ve bunu kaldır.
    if(direction.x >= speed*dt ){
        pos.x += speed*dt;
        direction.x -= speed*dt;
        lastDir = DIR_RIGHT;
    } else if (direction.x <= -speed*dt) {
        pos.x -= speed*dt;
        direction.x += speed*dt;
        lastDir = DIR_LEFT;
    } else { 
        direction.x = 0;
    }

    if(direction.y >= speed*dt){
        pos.y += speed*dt;
        direction.y -= speed*dt;
        lastDir = DIR_DOWN;
    } else if (direction.y <= -speed*dt) {
        pos.y -= speed*dt;
        direction.y += speed*dt;
        lastDir = DIR_UP;
    } else { 
        direction.y = 0;
    }
}


void enemys::draw(){
    Rectangle source = {
        0, 0,
        (float)text.width,
        (float)text.height
    };

    Rectangle dest = {
        pos.x + text.width / 2.0f, 
        pos.y + text.height / 2.0f,
        (float)text.width, 
        (float)text.height
    };

    Vector2 origin = {
        text.width / 2.0f,
        text.height / 2.0f
    };


    DrawTexturePro(text, source, dest, origin, lastDir*90, WHITE);
}