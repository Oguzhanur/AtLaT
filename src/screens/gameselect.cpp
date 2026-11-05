#include "screens/gameselect.hpp"

void gameselectScreen::start(){

}

void gameselectScreen::loop(){
    Vector2 mousePos = GetMousePosition();
    backBut.effectLoop(mousePos);

    for(int x=0; x<=GData->endedWawes; x++){
        episodeButtons[x].setActive(1);
        if(x>1) continue;
        episodeButtons[x].effectLoop(mousePos);

        if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT) && episodeButtons[x].isClicked(mousePos)){
            GData->curentWawe = x+1;
            GData->status = SCREEN_GAMEPLAY;
        }
    }

    if(IsMouseButtonReleased(MOUSE_BUTTON_LEFT)){
        if(backBut.isClicked(mousePos)){
            GData->status = SCREEN_MAINMENU;
        }
    }
}

void gameselectScreen::draw(){
    ClearBackground(GRAY);
    BeginMode2D(camera);
        backBut.draw();
        gui::drawText("SELECT EPİSODE", {300,150}, megaFont, BLACK);

        for(auto& but : episodeButtons){
            but.drawAdd();
        }
    EndMode2D();
}