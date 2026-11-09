#pragma once
#include "screens/base.hpp"

class settingsScreen : public baseScreen{
private:
    Texture2D playButT, button200x80Text;
    gui::texture background;
    gui::textButton backBut, langButton;
    gui::font mainFont, megaFont;
    gui::switchTextButton settingsNoti;
public:
    settingsScreen(ctx* GData) : baseScreen(GData),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        playButT(LoadTexture("data/gui/buttons/but450x150.png")),
        button200x80Text(LoadTexture("data/gui/buttons/button200x80.png")),
        settingsNoti(button200x80Text, LANG::settingsFullScreenButton[GData->lang], mainFont, BLACK, {850,180}),
        langButton(button200x80Text, LANG::Language[GData->lang] , mainFont, BLACK, {850,280}),
        backBut(playButT, LANG::MainMenu[GData->lang], megaFont, BLACK, {400,450}),
        background("data/gui/settingsBackground.png", {0,0})
    {}
    ~settingsScreen() override {
        UnloadTexture(playButT);
    }

    void start() override;
    void loop() override;
    void draw() override;
};