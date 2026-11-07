#include "screens/settings.hpp"

void settingsScreen::start(){

}

void settingsScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    backBut.effectLoop(mousePos);
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        if(backBut.isClicked(mousePos)){
            GData->status = SCREEN_MAINMENU;
        } else if (settingsNoti.isClicked(mousePos)){
            GData->fullscreen = !GData->fullscreen;
        }
    }
}

void settingsScreen::draw(){
    ClearBackground(GRAY);
    BeginMode2D(camera);
        backBut.draw();
        settingsNoti.draw(GData->fullscreen);
        gui::drawText("Tam ekran ayarı: ", {200,200}, megaFont, BLACK);
    EndMode2D();
}