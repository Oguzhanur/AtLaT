#pragma once
#include "screens/base.hpp"

class gameselectScreen : public baseScreen{
private:
    Texture2D basicBut, e1, e2, e3, e4, e5;
    gui::button episodeButton1, episodeButton2, episodeButton3, episodeButton4, episodeButton5;
    gui::textButton backBut;
    gui::font mainFont, megaFont;
public:
    gameselectScreen(ctx* GData) : baseScreen(GData),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        basicBut(LoadTexture("data/gui/buttons/but200x100.png")),
        backBut(basicBut, "Main Menu", mainFont, BLACK, {20,20}),

        e1(LoadTexture("data/gui/episode1but.png")),
        e2(LoadTexture("data/gui/episode2but.png")),
        e3(LoadTexture("data/gui/episode3but.png")),
        e4(LoadTexture("data/gui/episode4but.png")),
        e5(LoadTexture("data/gui/episode5but.png")),
        episodeButton1(e1, {150,350}),
        episodeButton2(e2, {400,350}),
        episodeButton3(e3, {650,350}),
        episodeButton4(e4, {900,225}),
        episodeButton5(e5, {900,475})
    {}
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