#include "screens/endScreen.hpp"

void endScreen::start(){

}

void endScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    playBut.effectLoop(mousePos);
    backBut.effectLoop(mousePos);
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        if(playBut.isClicked(mousePos)){
            GData->isPlayerWinnedGame = -1;
            GData->status = SCREEN_GAMEPLAY;
        }
        if(backBut.isClicked(mousePos)){
            GData->isPlayerWinnedGame = -1;
            GData->status = SCREEN_MAINMENU;
        }
    }
}

void endScreen::draw(){
    ClearBackground(GRAY);
    BeginMode2D(camera);
        playBut.draw();
        backBut.draw();

        if(GData->isPlayerWinnedGame==1){
            gui::drawCenteredText(LANG::endWin[GData->lang], {GData->ScreenSize.x/2,200}, megaFont, GREEN);
        } else if (GData->isPlayerWinnedGame==0) {
            gui::drawCenteredText(LANG::endLose[GData->lang], {GData->ScreenSize.x/2,200}, megaFont, RED);
        } else {
            gui::drawCenteredText(LANG::endEnd[GData->lang], {GData->ScreenSize.x/2,200}, megaFont, YELLOW);
        }
    EndMode2D();
}