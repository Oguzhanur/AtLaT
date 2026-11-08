#pragma once
#include "screens/base.hpp"


class mainMenuScreen : public baseScreen{
private:
    Texture2D ButtonBasic;
    gui::texture logo;
    gui::textButton playBut, settingsBut;
    gui::font mainFont, megaFont, megamegaFont;
public:
    mainMenuScreen(ctx* GData) : baseScreen(GData),
        ButtonBasic(LoadTexture("data/gui/buttons/but880x150.png")),
        playBut(ButtonBasic, LANG::Start[GData->lang], megaFont, BLACK, {200,350}),
        settingsBut(ButtonBasic, LANG::Settings[GData->lang], megaFont, BLACK, {200,530}),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        megamegaFont("data/font/Bungee-Regular.ttf", 128.f),
        logo("data/gui/logoBig.png", {350,57})
    {}
    ~mainMenuScreen() override {
        UnloadTexture(ButtonBasic);
    }

    void start() override;
    void loop() override;
    void draw() override;
};