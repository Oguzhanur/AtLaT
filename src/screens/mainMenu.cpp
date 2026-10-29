#include "screens/mainMenu.hpp"

void mainMenuScreen::start(){

}

void mainMenuScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(playBut.isClicked(mousePos)){
            GData->status = SCREEN_GAMEPLAY;
        }
    }
}

void mainMenuScreen::draw(){
    ClearBackground(GRAY);
    BeginMode2D(camera);
        playBut.draw();
        gui::drawText("START GAME", {430,640}, megaFont, BLACK);
    EndMode2D();
}