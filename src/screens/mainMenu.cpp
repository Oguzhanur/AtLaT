#include "screens/mainMenu.hpp"

void mainMenuScreen::start(){

}

void mainMenuScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    playBut.effectLoop(mousePos);
    settingsBut.effectLoop(mousePos);
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
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
    gui::drawText("AtLaT", {logo.getPos().x+230,100}, megamegaFont, BLACK);
    playBut.draw();
    settingsBut.draw();
    logo.drawEx(logo.getPos(), 2.f);
}