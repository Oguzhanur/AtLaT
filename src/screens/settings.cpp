#include "screens/settings.hpp"

void settingsScreen::start(){

}

void settingsScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    backBut.effectLoop(mousePos);
    langButton.effectLoop(mousePos);
    settingsNoti.effectLoop(mousePos);
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        if(backBut.isClicked(mousePos)){
            GData->status = SCREEN_MAINMENU;
        } else if(settingsNoti.isClicked(mousePos)){
            GData->fullscreen = !GData->fullscreen;
        } else if(langButton.isClicked(mousePos)){
            TraceLog(LOG_INFO, "LANG: %i", GData->lang);
            if(GData->lang+1<LANG_END){
                GData->lang++;
            } else {
                GData->lang = 0;
            }
            GData->status = SCREEN_SETTINGS;
        }
    }
}

void settingsScreen::draw(){
    ClearBackground(GRAY);
    BeginMode2D(camera);
        background.draw();
        backBut.draw();
        settingsNoti.draw(GData->fullscreen);
        gui::drawText(LANG::settingsFullScreenText[GData->lang], {200,settingsNoti.getPos().y+8}, megaFont, BLACK);

        langButton.draw();
        gui::drawText(LANG::settingsLangagesText[GData->lang], {200,langButton.getPos().y+8}, megaFont, BLACK);
    EndMode2D();
}