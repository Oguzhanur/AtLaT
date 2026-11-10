#include "screens/endScreen.hpp"

void endScreen::start(){

}

void endScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    playBut.effectLoop(mousePos);
    backBut.effectLoop(mousePos);
    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        if(playBut.isClicked(mousePos)){
            if(GData->isPlayerWinnedGame==1){
                GData->curentWawe++;
                GData->status = SCREEN_GAMEPLAY;
            } else {
                GData->isPlayerWinnedGame = -1;
                GData->status = SCREEN_GAMEPLAY;
            }
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
        background.draw();
        backBut.draw();

        if(GData->isPlayerWinnedGame==1){
            nextBut.draw();
            gui::drawCenteredText(LANG::endWin[GData->lang], {GData->ScreenSize.x/2,200}, megaFont, GREEN);
        } else if (GData->isPlayerWinnedGame==0) {
            playBut.draw();
            gui::drawCenteredText(LANG::endLose[GData->lang], {GData->ScreenSize.x/2,200}, megaFont, RED);
        } else {
            playBut.draw();
            gui::drawCenteredText(LANG::endEnd[GData->lang], {GData->ScreenSize.x/2,200}, megaFont, YELLOW);
        }
    EndMode2D();
}