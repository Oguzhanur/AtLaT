#include "screens/demoEndScreen.hpp"

void demoendScreen::start(){

}

void demoendScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    exitBut.effectLoop(mousePos);
    backBut.effectLoop(mousePos);
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        if(exitBut.isClicked(mousePos)){
            GData->status = SCREEN_CLOSE;
        }
        if(backBut.isClicked(mousePos)){
            GData->status = SCREEN_MAINMENU;
        }
    }
}

void demoendScreen::draw(){
    ClearBackground(GRAY);
    BeginMode2D(camera);
        background.draw();
        exitBut.draw();
        backBut.draw();

        gui::drawCenteredText(LANG::demoEndText[GData->lang], {GData->ScreenSize.x/2,200}, megaFont, GREEN);
    EndMode2D();
}