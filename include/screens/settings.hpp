#pragma once
#include "screens/base.hpp"

class settingsScreen : public baseScreen{
private:
    Texture2D playButT, button200x100Text;
    gui::textButton backBut;
    gui::font mainFont, megaFont;
    gui::switchTextButton settingsNoti;
public:
    settingsScreen(ctx* GData) : baseScreen(GData),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        playButT(LoadTexture("data/gui/buttons/but450x150.png")),
        button200x100Text(LoadTexture("data/gui/button200x100.png")),
        settingsNoti(button200x100Text, "Tam Ekran", "Pencereli", mainFont, BLACK, {800,175}),
        backBut(playButT, "Ana Menü", megaFont, BLACK, {400,500})
    {}
    ~settingsScreen() override {
        UnloadTexture(playButT);
    }

    void start() override;
    void loop() override;
    void draw() override;
};