#include "gui/textures.hpp"

gui::texture::texture(const std::string& path, Vector2 pos) : pos(pos){
    text = LoadTexture(path.c_str());
}
gui::texture::~texture(){
    UnloadTexture(text);
}

void gui::texture::draw(){
    DrawTexture(text, pos.x, pos.y, WHITE);
}
void gui::texture::drawEx(Vector2 pos, float scale){
    pos = pos;
    DrawTextureEx(text, pos, 0.f, scale, WHITE);
}