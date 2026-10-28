#include "screens/base.hpp"

class endScreen : public baseScreen{
private:
    Texture2D playButT;
    gui::button playBut, backBut;
    gui::font mainFont, megaFont;
public:
    endScreen(ctx* GData) : baseScreen(GData),
        playButT(LoadTexture("data/gui/buttons/but450x150.png")),
        playBut(playButT, {100,600}),
        backBut(playButT, {600,600}),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f)
    {}
    ~endScreen() override {
        UnloadTexture(playButT);
    }

    void start() override;
    void loop() override;
    void draw() override;
};