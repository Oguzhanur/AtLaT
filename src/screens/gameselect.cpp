#include "screens/gameselect.hpp"

void gameselectScreen::start(){

}

void gameselectScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(backBut.isClicked(mousePos)){
            GData->status = SCREEN_MAINMENU;
        }

        // episodes
        if(episodeButton1.isClicked(mousePos)){
            GData->status = SCREEN_GAMEPLAY;
        }
    }
}

void gameselectScreen::draw(){
    ClearBackground(GRAY);
    BeginMode2D(camera);
        backBut.draw();
        gui::drawText("SELECT EPİSODE", {300,150}, megaFont, BLACK);
        episodeButton1.draw();
        episodeButton2.draw();
        episodeButton3.draw();
        episodeButton4.draw();
        episodeButton5.draw();
    EndMode2D();
}