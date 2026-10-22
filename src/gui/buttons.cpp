#include "gui/buttons.hpp"

bool gui::button::isClicked(Vector2 mousePos){
    buttonRec = {pos.x, pos.y, (float)text->width, (float)text->height};

    return CheckCollisionPointRec(mousePos, buttonRec);
}
void gui::button::draw(){
    DrawTextureEx(*text, pos, 0.f, 1.f, WHITE);
}