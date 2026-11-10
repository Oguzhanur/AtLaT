#pragma once
#include "screens/base.hpp"

class demoendScreen : public baseScreen{
private:
    Texture2D mainButT;
    gui::textButton exitBut, backBut;
    gui::texture background;
    gui::font mainFont, megaFont;
public:
    demoendScreen(ctx* GData) : baseScreen(GData),
        mainButT(LoadTexture("data/gui/buttons/but450x150.png")),
        exitBut(mainButT, LANG::ExitGame[GData->lang], megaFont, BLACK, {160,450}),
        backBut(mainButT, LANG::MainMenu[GData->lang], megaFont, BLACK, {660,450}),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        background("data/gui/demoEndScreen.png", {0,0})
    {}
    ~demoendScreen() override {
        UnloadTexture(mainButT);
    }

    void start() override;
    void loop() override;
    void draw() override;
};