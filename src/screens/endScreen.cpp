#include "screens/endScreen.hpp"

void endScreen::start(){

}

void endScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(playBut.isClicked(mousePos)){
            GData->status = SCREEN_GAMEPLAY;
        }
        if(backBut.isClicked(mousePos)){
            GData->status = SCREEN_MAINMENU;
        }
    }
}

void endScreen::draw(){
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);
        playBut.draw();
        gui::drawText("Play Again", {120,640}, megaFont, BLACK);

        backBut.draw();
        gui::drawText("Main Menu", {680,640}, megaFont, BLACK);

        if(GData->isPlayerWinnedGame){
            gui::drawText("YOU WİN", {420,200}, megaFont, GREEN);
        } else {
            gui::drawText("YOU LOSE", {420,200}, megaFont, RED);
        }
    EndMode2D();
}