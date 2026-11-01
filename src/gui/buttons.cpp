#include "gui/buttons.hpp"


bool gui::button::isClicked(Vector2 mousePos){
    buttonRec = {pos.x, pos.y, (float)text->width, (float)text->height};

    return CheckCollisionPointRec(mousePos, buttonRec);
}
void gui::button::effectLoop(Vector2 mousePos){

    if(this->isClicked(mousePos)){
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
            scale = 0.95;
        } else {
            scale = 1.05;
        }
        

        if(Vector2Equals(oldPos, {0,0})) oldPos = pos;

        Vector2 center = {oldPos.x + text->width / 2.f, oldPos.y + text->height / 2.f};

        pos = {center.x - (text->width * scale) / 2.f, center.y - (text->height * scale) / 2.f};
        
    } else {
        if(!Vector2Equals(oldPos, {0,0})) pos = oldPos;
        oldPos = {0,0};
        scale = 1.0;
    }
    
}

void gui::button::draw(){
    DrawTextureEx(*text, pos, 0.f, scale, buttonColor);
}


void gui::textButton::draw(){
    DrawTextureEx(*text, pos, 0.f, scale, buttonColor);

    Vector2 centerPos = gui::centeringTextEx(textData, scale, Vector2Add(pos, {(text->width*scale)/2.f, (text->height*scale)/2.f}), fontData);

    color.a = buttonColor.a;
    DrawTextEx(fontData.getFontData(), textData.c_str(), centerPos, fontData.getFontSize()*scale, 2, color);
}

void gui::switchButton::draw(bool isOn){
    if(isOn){  
        DrawTextureEx(*text , pos, 0.f, scale, buttonColor);
    } else {
        DrawTextureEx(*text2, pos, 0.f, scale, buttonColor);
    }
}