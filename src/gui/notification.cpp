#include "gui/notification.hpp"

void notification::loop(float dt){
    endTime -= dt;
    if(endTime <= 0){
        isActive = 0;
    }
}

void notification::draw(){
    if(isActive){
        Vector2 textPos;
        if(text != nullptr){
            DrawTextureEx(*text, pos, 0.f, 1.f, (Color){ 255, 255, 255, (255.f/duraction)*endTime });
            textPos = gui::centeringText(data, Vector2Add(pos, {(float)text->width/2, (float)text->height/2}), fontData);
        } else {
            textPos = pos;
        }

        gui::drawText(data, textPos, fontData, (Color){ 255, 255, 255, (255.f/duraction)*endTime });
    }
}