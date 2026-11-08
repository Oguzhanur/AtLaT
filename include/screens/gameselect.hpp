#pragma once
#include "screens/base.hpp"

class gameselectScreen : public baseScreen{
private:
    Texture2D basicBut, e1, e2, e3, e4, e5, hiddene;
    std::vector<gui::hiddenButton> episodeButtons;
    gui::textButton backBut;
    gui::font mainFont, megaFont;
public:
    gameselectScreen(ctx* GData) : baseScreen(GData),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        basicBut(LoadTexture("data/gui/buttons/but200x100.png")),
        backBut(basicBut, LANG::MainMenu[GData->lang], mainFont, BLACK, {20,20}),
        e1(LoadTexture("data/gui/episode1but.png")),
        e2(LoadTexture("data/gui/episode2but.png")),
        e3(LoadTexture("data/gui/episode3but.png")),
        e4(LoadTexture("data/gui/episode4but.png")),
        e5(LoadTexture("data/gui/episode5but.png")),
        hiddene(LoadTexture("data/gui/episodebutNoAc.png"))
    {
        episodeButtons.reserve(5);
        episodeButtons.push_back(gui::hiddenButton{e1, hiddene, {150,350}, 0});
        episodeButtons.push_back(gui::hiddenButton{e2, hiddene, {400,350}, 0});
        episodeButtons.push_back(gui::hiddenButton{e3, hiddene, {650,350}, 0});
        episodeButtons.push_back(gui::hiddenButton{e4, hiddene, {900,225}, 0});
        episodeButtons.push_back(gui::hiddenButton{e5, hiddene, {900,475}, 0});
    }
    ~gameselectScreen() override {
        UnloadTexture(basicBut);
        UnloadTexture(e1);
        UnloadTexture(e2);
        UnloadTexture(e3);
        UnloadTexture(e4);
        UnloadTexture(e5);
    }

    void start() override;
    void loop() override;
    void draw() override;
};