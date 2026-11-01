#include "screens/mainMenu.hpp"

void mainMenuScreen::start(){

}

void mainMenuScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        if(playBut.isClicked(mousePos)){
            GData->status = SCREEN_GAMESELECT;
        }
        if(settingsBut.isClicked(mousePos)){
            GData->status = SCREEN_SETTINGS;
        }
    }
}

void mainMenuScreen::draw(){
    ClearBackground(GRAY);
    BeginMode2D(camera);
        
    EndMode2D();
    gui::drawText("AtLaT", {450,100}, megamegaFont, BLACK);
    playBut.draw();
    settingsBut.draw();
}