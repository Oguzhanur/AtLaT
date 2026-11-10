#pragma once
#include "screens/base.hpp"

class endScreen : public baseScreen{
private:
    Texture2D playButT;
    gui::textButton playBut, backBut, nextBut;
    gui::texture background;
    gui::font mainFont, megaFont;
public:
    endScreen(ctx* GData) : baseScreen(GData),
        playButT(LoadTexture("data/gui/buttons/but450x150.png")),
        playBut(playButT, LANG::endRetry[GData->lang], megaFont, BLACK, {160,450}),
        nextBut(playButT, LANG::endNext[GData->lang], megaFont, BLACK, {160,450}),
        backBut(playButT, LANG::MainMenu[GData->lang], megaFont, BLACK, {660,450}),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        background("data/gui/endScreen.png", {0,0})
    {}
    ~endScreen() override {
        UnloadTexture(playButT);
    }

    void start() override;
    void loop() override;
    void draw() override;
};