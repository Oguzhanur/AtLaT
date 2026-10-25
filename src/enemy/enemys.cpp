#include "enemy/enemys.hpp"


void enemys::aiLoop(mapMan& man, const float dt){
    if(direction.x == 0 && direction.y == 0){
        Vector2 newPos = pos;
        float movementSpeed = 32;
        int size = 0;

        newPos.x+=size+movementSpeed;

        if (direction.x != 0 || direction.y != 0) timeBackup = 0.0f;

        if (man.isInCollionWithID(newPos, {(float)text->width, (float)text->height}, 1) && lastDir != DIR_LEFT && !man.isInCollionWithID(newPos, {(float)text->width, (float)text->height}, 2)){
            //* ------- SAĞ -------
            direction.x = movementSpeed;
        } else {
            //* ------- SOL -------
            newPos.x-=size+movementSpeed*2;
            if(man.isInCollionWithID(newPos, {(float)text->width, (float)text->height}, 1) && lastDir != DIR_RIGHT && !man.isInCollionWithID(newPos, {(float)text->width, (float)text->height}, 2)){
                direction.x = -movementSpeed;
            } else {
                newPos.x = pos.x;
                newPos.y += size+movementSpeed;
                if(man.isInCollionWithID(newPos, {(float)text->width, (float)text->height}, 1) && lastDir != DIR_UP && !man.isInCollionWithID(newPos, {(float)text->width, (float)text->height}, 2)){
                    //* ------- AŞŞAĞI -------
                    direction.y = movementSpeed;
                } else {
                    //* ------- YUKARI -------
                    newPos.y -= size+movementSpeed*2;
                    if(man.isInCollionWithID(newPos, {(float)text->width, (float)text->height}, 1) && lastDir != DIR_DOWN && !man.isInCollionWithID(newPos, {(float)text->width, (float)text->height}, 2)){
                        direction.y = -movementSpeed;
                    } else {
                        //* ------- HAREKET YOKKK -------
                        direction = {0,0};
                        timeBackup += dt;
                        if(timeBackup>=0.5f){
                            endData = 1;
                        }
                    }
                }
            }
        }
    }
}

void enemys::move(float dt){ //? Hareketlerin uyumlu olması için 0.001 altı değerler yuvarlanıyor!!!!
    if(direction.x > 0.001f){ //* X pozitifse
        float step = std::min(direction.x, stats.speed*dt);
        pos.x+=step;
        direction.x-=step;
        lastDir = DIR_RIGHT;
    } else if (direction.x < -0.001f) { //* X negatifse
        float step = std::min(-direction.x, stats.speed*dt);
        pos.x-=step;
        direction.x+=step;
        lastDir = DIR_LEFT;
    } else {  //* X 0sa
        direction.x = 0;
        pos.x += direction.x;
        pos.x = std::round(pos.x);}

    if(direction.y > 0.001f){ //* y = +
        float step = std::min(direction.y, stats.speed*dt);
        pos.y+=step;
        direction.y-=step;
        lastDir = DIR_DOWN;
    } else if (direction.y < -0.001f) { //* y = -
        float step = std::min(-direction.y, stats.speed*dt);
        pos.y-=step;
        direction.y+=step;
        lastDir = DIR_UP;
    } else { //* y = 0
        direction.y = 0;
        pos.y += direction.y;
        pos.y = std::round(pos.y);
    }
}


void enemys::draw(){
    if(active){
        Rectangle source = {
            0, 0,
            (float)text->width,
            (float)text->height
        };

        Rectangle dest = {
            pos.x + text->width / 2.0f, 
            pos.y + text->height / 2.0f,
            (float)text->width, 
            (float)text->height
        };

        Vector2 origin = {
            text->width / 2.0f,
            text->height / 2.0f
        };


        DrawTexturePro(*text, source, dest, origin, lastDir*90, WHITE);
    }
}