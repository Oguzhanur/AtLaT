#include "gui/buttons.hpp"

gui::button::button(const std::string& path, Vector2 pos) : pos(pos){
    texture = LoadTexture(path.c_str());

    buttonRec = {pos.x, pos.y, (float)texture.width, (float)texture.height};
}
gui::button::~button(){
    UnloadTexture(texture);
}
bool gui::button::isClicked(Vector2 mousePos){
    return CheckCollisionPointRec(mousePos, buttonRec);
}
void gui::button::draw(){
    DrawTextureEx(texture, pos, 0.f, 1.f, WHITE);
}