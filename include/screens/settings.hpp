#pragma once
#include "screens/base.hpp"

class settingsScreen : public baseScreen{
private:
    Texture2D playButT;
    gui::textButton backBut;
    gui::font mainFont, megaFont;
public:
    settingsScreen(ctx* GData) : baseScreen(GData),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        playButT(LoadTexture("data/gui/buttons/but450x150.png")),
        backBut(playButT, "Ana Menü", megaFont, BLACK, {400,500})
    {}
    ~settingsScreen() override {
        UnloadTexture(playButT);
    }

    void start() override;
    void loop() override;
    void draw() override;
};