#include "screens/settings.hpp"

void settingsScreen::start(){

}

void settingsScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    backBut.effectLoop(mousePos);
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        if(backBut.isClicked(mousePos)){
            GData->status = SCREEN_MAINMENU;
        }
    }
}

void settingsScreen::draw(){
    ClearBackground(RAYWHITE);
    BeginMode2D(camera);
        backBut.draw();
    EndMode2D();
}