#pragma once
#include <raylib.h>
#include <string>

enum TowerType{
    T_NOTOWER, T_TOWER1, T_TOWER2, T_TOWER3, T_TOWER4, T_TOWER5,
};

class tower1{
private:
    Vector2 pos;
    Texture2D text;
public:
    tower1(const std::string& path);
    ~tower1();

    Texture2D getTexture() {return text;};

    void drawEx(Vector2 pos);
};
