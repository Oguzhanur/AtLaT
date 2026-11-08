#pragma once
#include "screens/base.hpp"

class settingsScreen : public baseScreen{
private:
    Texture2D playButT, button200x100Text;
    gui::textButton backBut, langButton;
    gui::font mainFont, megaFont;
    gui::switchTextButton settingsNoti;
public:
    settingsScreen(ctx* GData) : baseScreen(GData),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        playButT(LoadTexture("data/gui/buttons/but450x150.png")),
        button200x100Text(LoadTexture("data/gui/buttons/button200x100.png")),
        backBut(playButT, LANG::MainMenu[GData->lang], megaFont, BLACK, {400,500}),
        settingsNoti(button200x100Text, LANG::settingsFullScreenButton[GData->lang], mainFont, BLACK, {800,175}),
        langButton(button200x100Text, LANG::Language[GData->lang] , mainFont, BLACK, {800,300})
    {}
    ~settingsScreen() override {
        UnloadTexture(playButT);
    }

    void start() override;
    void loop() override;
    void draw() override;
};