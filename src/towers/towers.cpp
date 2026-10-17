#include "towers/towers.hpp"

tower1::tower1(const std::string& path) : pos(pos){
    text = LoadTexture(path.c_str());
}
tower1::~tower1(){
    UnloadTexture(text);
}

void tower1::drawEx(Vector2 pos){
    pos = pos;
    DrawTextureEx(text, pos, 0.f, 1.f, WHITE);
}