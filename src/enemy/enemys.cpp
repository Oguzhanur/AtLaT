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
        int movementSpeed = 32;
        int size = 0;

        newPos.x+=size+movementSpeed;

        if (man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 1) && lastDir != DIR_LEFT && !man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 2)){
            //* ------- SAĞ -------
            TraceLog(LOG_INFO, "Sağa");
            direction.x = movementSpeed;
        } else {
            //* ------- SOL -------
            newPos.x-=size+movementSpeed*2;
            if(man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 1) && lastDir != DIR_RIGHT && !man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 2)){
                TraceLog(LOG_INFO, "Sola");
                direction.x = -movementSpeed;
            } else {
                newPos.x = pos.x;
                newPos.y += size+movementSpeed;
                if(man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 1) && lastDir != DIR_UP && !man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 2)){
                    //* ------- AŞŞAĞI -------
                    TraceLog(LOG_INFO, "Aşşağı");
                    direction.y = movementSpeed;
                } else {
                    //* ------- YUKARI -------
                    newPos.y -= size+movementSpeed*2;
                    if(man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 1) && lastDir != DIR_DOWN && !man.isInCollionWithID(newPos, {(float)text.width, (float)text.height}, 2)){
                        TraceLog(LOG_INFO, "Yukarı");
                        direction.y = -movementSpeed;
                    } else {
                        //* ------- HAREKET YOKKK -------
                        TraceLog(LOG_INFO, "Hareket yok");
                        direction = {0,0};
                    }
                }
            }
        }
    }
}

void enemys::move(){
    TraceLog(LOG_INFO, "last: {%i}", lastDir);
    TraceLog(LOG_INFO, "dir: {%f, %f}", direction.x, direction.y);
    if(direction.x >= speed ){
        pos.x += speed;
        direction.x -= speed;
        lastDir = DIR_RIGHT;
    } else if (direction.x <= -speed) {
        pos.x -= speed;
        direction.x += speed;
        lastDir = DIR_LEFT;
    } else { 
        direction.x = 0;
    }

    if(direction.y >= speed){
        pos.y += speed;
        direction.y -= speed;
        lastDir = DIR_DOWN;
    } else if (direction.y <= -speed) {
        pos.y -= speed;
        direction.y += speed;
        lastDir = DIR_UP;
    } else { 
        direction.y = 0;
    }
}


void enemys::draw(){
    DrawTextureEx(text, pos, 0.f, 1.f, WHITE);
}