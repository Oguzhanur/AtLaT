#include "screens/base.hpp"


class mainMenuScreen : public baseScreen{
private:
    Texture2D playButT;
    gui::button playBut;
    gui::font mainFont, megaFont;
public:
    mainMenuScreen(ctx* GData) : baseScreen(GData),
        playButT(LoadTexture("data/gui/buttons/but880x150.png")),
        playBut(playButT, {200,600}),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        megaFont("data/font/Bungee-Regular.ttf", 64.f)
    {}
    ~mainMenuScreen() override {
        UnloadTexture(playButT);
    }

    void start() override;
    void loop() override;
    void draw() override;
};