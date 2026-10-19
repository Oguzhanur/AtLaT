#include "towers/towers.hpp"

void tower1::draw(){
    if (text->id == 0) {
        TraceLog(LOG_ERROR, "Texture yuklenemedi!");
    }
    DrawTextureEx(*text, pos, 0.f, 1.f, WHITE);
}

void tower1::drawEx(Vector2 pos){
    pos = pos;
    DrawTextureEx(*text, pos, 0.f, 1.f, WHITE);
}
