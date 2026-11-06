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
private:
    int alpha=255;
    bool isActive=1;
    float endTime;
    float duraction;
    Texture2D* text;
    gui::font& fontData;
    std::string data;
    int type;
public:
    notification(Texture2D& text, gui::font& fontData, std::string data, int type, int duraction): 
        text(&text), fontData(fontData), data(data), type(type), duraction(duraction), endTime(duraction) {}
    ~notification() = default;

    bool getActive() {return isActive;};

    void loop(float dt);
    void draw();
};
