#pragma once

#include <raylib.h>
#include <raymath.h>
#include <string>
#include "gui/text.hpp"

enum notificationType{
    NOTİ_NULL,
    NOTİ_INFO
};

class notification{
protected:
    int alpha=255;
    bool isActive=1;
    float endTime;
    float duraction;
    Texture2D* text = nullptr;
    gui::font& fontData;
    std::string data;
    Vector2 pos = {450.f, 20.f};
    int type;
public:
    notification(gui::font& fontData, std::string data, int type, float duraction, Vector2 pos): 
        fontData(fontData), data(data), type(type), duraction(duraction), endTime(duraction), pos(pos) {}
    ~notification() = default;

    void setPos(Vector2 newPos) {pos = newPos;};
    void setData(std::string newData) {data = newData;};

    bool getActive() const {return isActive;};

    void loop(float dt);
    void draw();
};