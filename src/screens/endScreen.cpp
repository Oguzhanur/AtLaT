#include "screens/endScreen.hpp"

void endScreen::start(){

}

void endScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
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
        backBut.draw();

        if(GData->isPlayerWinnedGame){
            gui::drawCenteredText("YOU WİN", {GData->ScreenSize.x/2,200}, megaFont, GREEN);
        } else {
            gui::drawCenteredText("YOU LOSE", {GData->ScreenSize.x/2,200}, megaFont, RED);
        }
    EndMode2D();
}