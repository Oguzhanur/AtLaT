#include <raylib.h>
#include <vector>
#include <ostream>
#include <algorithm>
#include <cmath>
#include <format>

#include "core/ctx.hpp"

#include "map/mapMan.hpp"
#include "gui/buttons.hpp"
#include "gui/textures.hpp"
#include "gui/healthBar.hpp"
#include "gui/text.hpp"

#include "towers/towers.hpp"
#include "enemy/enemys.hpp"

#include "enemy/wawe.hpp"


int main(void) {
    ctx GData;

    TraceLog(LOG_INFO, "MAIN BASLADI");
    InitWindow(GData.ScreenSize.x, GData.ScreenSize.y, "Tank Oyunu");

    SetTargetFPS(60);

    mapMan mapMan1;

    // Base
    int money = 9999;
    float baseHealth = 100.f;
    healthBar hBar({20,20}, {400,50}, baseHealth);

    // Kamera
    Camera2D camera = { 0 };
    camera.target = {GData.ScreenSize.x/2, GData.ScreenSize.y/2};
    camera.offset = {GData.ScreenSize.x/2, GData.ScreenSize.y/2};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    // Selected
    float frameTime = 0.f;
    float TimeAsFrame = 0.f;
    int selectedBut = 0;
    int selectedTower = 0;
    int selectedTData = 0;

    // ---------------------------------- EKRANLAR ----------------------------------


    // ---------------------------------- ARAYÜZ ----------------------------------
    Color BColor{0,100,0,100};

    // Kule Geliştirme / Bilgi / Silme
    gui::texture towerInfoMenu("data/gui/towerInfoMenu.png", {0,125});
    Texture2D tUpdateM = LoadTexture("data/gui/towerUpgrade.png");
    Texture2D tDeleteM = LoadTexture("data/gui/towerRemove.png");
    gui::button towerUpdateButton(tUpdateM, {20, 550});
    gui::button towerRemoveButton(tDeleteM, {20, 675});
    
    // Sağ Menü
    Texture2D startButtonM = LoadTexture("data/gui/startButton.png");
    Texture2D stopButtonM = LoadTexture("data/gui/stopButton.png");
    gui::switchButton waweBut(startButtonM, stopButtonM, {1000, 550});

    gui::texture rightMenu("data/gui/RMenu.png", {1000,0});

    // Fonlar
    gui::font mainFont("data/font/Bungee-Regular.ttf", 32.f);
    gui::font smallFont("data/font/Bungee-Regular.ttf", 24.f);

    // ---------------------------------- KULELER ----------------------------------
    std::vector<std::vector<towerStats>> TStats = { //? Hasar, Alan, Saldırı Hızı, Maliyet
        {   { 5.f, 150.f, 0.5f, 150, {TS_NULL}},
            { 5.f, 150.f, 0.1f, 200, {TS_NULL}},
            {10.f, 150.f, 0.1f, 450, {TS_NULL}}},

        {   {15.f, 300.f, 2.0f, 200, {TS_NULL}},
            {25.f, 600.f, 4.0f, 100, {TS_NULL}},
            {50.f, 600.f, 2.0f, 250, {TS_NULL}}},

        {   {10.f, 150.f, 2.0f, 500, {TS_MULTIPLE}},
            {15.f, 200.f, 4.0f, 250, {TS_MULTIPLE}},
            {30.f, 300.f, 2.0f, 700, {TS_MULTIPLE}}},

        {   { 2.f, 150.f, 2.0f, 250, {TS_SLOW}},
            {15.f, 200.f, 1.0f, 100, {TS_SLOW}},
            {30.f, 300.f, 0.5f, 100, {TS_SLOW}}}
    };


    std::vector<towerTexturesData> towerTexture;

    std::vector<gui::button> towerButtons;

    //* Kule 1 - Normal
    towerTexturesData t1;
    t1.buttonTexture = LoadTexture("data/items/item1But.png");
    t1.towerTexture = LoadTexture("data/items/item1.png");
    t1.bulletTexture = LoadTexture("data/items/item1Bul.png");
    //TODO: Bullet png'si ile oynayan kullanıcı direk oyuna etki edemesin.

    towerButtons.emplace_back(gui::button{t1.buttonTexture, {1100,0}});

    towerTexture.push_back(t1);

    //* Kule 2 - Büyük range / Yüksek hasar
    towerTexturesData t2;
    t2.buttonTexture = LoadTexture("data/items/item2But.png");
    t2.towerTexture = LoadTexture("data/items/item2.png");
    t2.bulletTexture = LoadTexture("data/items/item2Bul.png");

    towerButtons.emplace_back(gui::button{t2.buttonTexture, {1000,0}});

    towerTexture.push_back(t2);

    //* Kule 3 - Alan hasarı / orta hasar
    towerTexturesData t3;
    t3.buttonTexture = LoadTexture("data/items/item3But.png");
    t3.towerTexture = LoadTexture("data/items/item3.png");
    t3.bulletTexture = LoadTexture("data/items/item3Bul.png");

    towerButtons.emplace_back(gui::button{t3.buttonTexture, {1000,100}});

    towerTexture.push_back(t3);

    //* Kule 3 - Yavaşlatma
    towerTexturesData t4;
    t4.buttonTexture = LoadTexture("data/items/item4But.png");
    t4.towerTexture = LoadTexture("data/items/item4.png");
    t4.bulletTexture = LoadTexture("data/items/item4Bul.png");

    towerButtons.emplace_back(gui::button{t4.buttonTexture, {1100,100}});

    towerTexture.push_back(t4);


    // ---------------------------------- DÜŞMANLAR ----------------------------------
    std::vector<Texture2D> enemyTextures;
    enemyTextures.push_back(LoadTexture("data/enemys/enemy.png"));
    enemyTextures.push_back(LoadTexture("data/enemys/enemySpeed.png"));

    std::vector<enemyStats> eStats = {
        {25.f, 25.f, 28.f},
        {10.f, 10.f, 200.f}
    };

    std::vector<tower1> placedTowers;
    std::vector<enemys> enemysComming;
    std::vector<Bullet> bullets;

    // Wawe
    int endStatus = 0;
    int currentWawe = 0;
    bool waweIsReady = 1;
    std::vector<wawe> wawes{ // Olduğu Wawe / Wawe başlayınca geçen süre / Kule / Sayısı / Aralık
        {0, 1.f , E_2, 1, 0.1},
        {1, 1.f , E_2, 10, 0.1},
        {1, 1.f , E_1, 5, .5},
        {2, 1.f , E_2, 50, 0.1},
        {2, 1.f , E_1, 10, 1},
        {3, 1.f , E_1, 100, 0.01},
        {3, 3.f , E_1, 250, 0.01}
    };

    // ---------------------------------- LOOP ----------------------------------
    while (!WindowShouldClose()){
        endStatus = 1;

        frameTime = GetFrameTime() * GData.gameSpeed; // Frame arası süre
        TimeAsFrame += frameTime;   // Geçen frame sayısı
        // Kamera hareketleri
        if(IsKeyDown(KEY_Q) && camera.zoom < 2.f){
            camera.zoom += 0.01f;
        } else if (IsKeyDown(KEY_E) && camera.zoom > 0.1f) {
            camera.zoom -= 0.01f;
        }

        if (IsKeyDown(KEY_W)){
            camera.target.y += -5;
        } else if (IsKeyDown(KEY_S)){
            camera.target.y +=  5;
        } if (IsKeyDown(KEY_A)){
            camera.target.x += -5;
        } else if (IsKeyDown(KEY_D)){
            camera.target.x +=  5;
        }

        // Ai ve arka sistemler
        for (enemys& enemy : enemysComming){
            enemy.effectsLoop(frameTime);
            enemy.aiLoop(mapMan1, frameTime);
            enemy.move(frameTime);
                    
            if(enemy.getEndData()==1){
                baseHealth-=enemy.getStats().health;
                enemy.kill();
            }

            endStatus=0;
        }


        for (Bullet& bul : bullets){
            if(bul.getActive()){ 
                std::vector<int> specials = bul.getSpecials();
                bul.updateBullet(frameTime);

                for (enemys& enemy : enemysComming){
                    if (CheckCollisionPointCircle(enemy.getPos(), bul.getPos(), 32) && enemy.getActive()){
                        bul.killBullet();
                        enemy.attack(bul.getDamage());
                        money += bul.getDamage();


                        // Çoklu hasar
                        bool isMult = 0, isSlow = 1;
                        for(int s : specials){
                            if(s == TS_MULTIPLE){
                                isMult = 1;
                            } else if (s == TS_SLOW){
                                isSlow = 1;
                            }
                        }

                        if(isSlow) enemy.addEffect({EFFECT_SLOW, 5.f, 0.f});

                        if(!isMult) break;
                    }
                }
            }
        }

        // --------------------------- KULE -------------------
        for (tower1& tower : placedTowers){
            if(!tower.getBulletIsReady(TimeAsFrame)) continue;

            for (enemys& enemy : enemysComming){
                if (!enemy.getActive()) continue;

                const towerStats& stats = tower.getStats();
                if(CheckCollisionCircleRec(tower.getCenter(), stats.range, enemy.getRec())){
                    bullets.push_back(Bullet{towerTexture[tower.getType()-1].bulletTexture, tower.getCenter(), enemy.getPosPtr(), 1500.f, stats.damage, tower.getStats().specials});
                    tower.setTimer(TimeAsFrame);
                    break;
                }
            }
        }


        // Wawe'ler
        waweIsReady = 1;
        for (wawe& w : wawes){
            if (w.getActive()){
                endStatus = 0;
                if(currentWawe == w.getWawe() && w.getActive()){
                    waweIsReady = 0;

                    if(TimeAsFrame>+w.getSavedClock()+w.getInterval() && TimeAsFrame > w.getTimeAsFrame()){
                        w.saveTime(TimeAsFrame);
                        enemysComming.emplace_back(enemyTextures[w.getTowerType()-1], Vector2{0, 192}, eStats[w.getTowerType()-1]);
                        w.countN();
                    }
                }
            }
        }

        // Oyun kaybetme
        if(baseHealth<=0.f){
            endStatus = -1;
        }

        // Temizlik
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& bullet) {return !bullet.getActive();}), bullets.end()
        );

        enemysComming.erase(
            std::remove_if(enemysComming.begin(), enemysComming.end(), [](const enemys& enemy) {return !enemy.getActive();}), enemysComming.end()
        );

        placedTowers.erase(
            std::remove_if(placedTowers.begin(), placedTowers.end(), [](const tower1& tower) {return !tower.getActive();}), placedTowers.end()
        );
        

        // ---------------------------------- ÇİZİMLER ----------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode2D(camera);

                mapMan1.draw();

                if(selectedBut>0 && selectedBut-1 < towerTexture.size()){
                    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                    Vector2 newPos = { worldPos.x-towerTexture[selectedBut-1].towerTexture.width/2, 
                                       worldPos.y-towerTexture[selectedBut-1].towerTexture.height/2 };
                    DrawTextureEx(towerTexture[selectedBut-1].towerTexture, newPos, 0.f, 1.f, WHITE);
                    
                }

                for (tower1& tower : placedTowers){
                    tower.draw();}

                for (Bullet& bul : bullets){
                    if (bul.getActive()) bul.draw();}

                for (enemys& enemy : enemysComming){ 
                    if (enemy.getActive()) enemy.draw();}

            EndMode2D();
        //* --------------------------- ÇİZİM BAŞLADI ---------------------------------------
            // Arayüz
            rightMenu.draw();

            for(int x=1; x<=towerButtons.size(); x++){
                towerButtons[x-1].draw();
            }

            if(selectedTower!=0){
                DrawCircleV(placedTowers[selectedTower-1].getCenter(), placedTowers[selectedTower-1].getStats().range, BColor);
                
                towerInfoMenu.draw();
                towerStats s = placedTowers[selectedTower-1].getStats();
                gui::drawText("Saldırı Hızı: " + gui::floatToStr(s.attackSpeed), {10,150}, smallFont, BLACK);
                gui::drawText("Saldırı Gücü: " + gui::floatToStr(s.damage), {10,200}, smallFont, BLACK);
                gui::drawText("Saldırı Alanı: " + gui::floatToStr(s.range), {10,250}, smallFont, BLACK);
                
                towerUpdateButton.draw();
                towerRemoveButton.draw();
                
                if(placedTowers[selectedTower-1].isInMaxLevel()){
                    gui::drawText("Maxsimum level", {20,520}, smallFont, BLACK);
                } else {
                    towerStats nextStats = placedTowers[selectedTower-1].getNextStats();

                    gui::drawText("Geliştirme: " + gui::floatToStr(nextStats.cost), {22,520}, smallFont, BLACK);
                }

            }


            hBar.draw(baseHealth);

            Vector2 hPos = hBar.getPos();
            Vector2 hSize = hBar.getSize();

            gui::drawText(hBar.getAsText(baseHealth), {hPos.x, hPos.y+hSize.y+10}, mainFont, WHITE);

            std::string moneyText = "Money: " + std::to_string(money);
            gui::drawText(moneyText, {800,20}, mainFont, Color{255,215,0,255});

            std::string waweText = "Wawe: " + std::to_string(currentWawe);
            gui::drawText(waweText, {1010, 520}, mainFont, BLACK);

            waweBut.draw(waweIsReady);

            if(endStatus==1){
                gui::drawText("GAME OVER: YOU WİN", {600, 100}, mainFont, GREEN);
                //TODO: Oyun kazanma ekranı
            } else if (endStatus==-1){
                gui::drawText("GAME OVER: YOU LOSE", {600, 100}, mainFont, RED);
                //TODO: Oyun kaybetme ekranı
            }

        EndDrawing();
        //* --------------------------- ÇİZİM BİTTİ ---------------------------------------
        

        // -------------------------------- BUTONLAR --------------------------------
        Vector2 mousePos = GetMousePosition();

        if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
            selectedTData = 0;

            if(selectedBut!=0){
                Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), camera);
                TileData data = mapMan1.getTileByPos(worldPos);

                if(data.type>0){
                    for (tower1& tower : placedTowers){
                        if(mapMan1.getRealPos(data.tilePos).x == tower.getPos().x && mapMan1.getRealPos(data.tilePos).y == tower.getPos().y) data.isTileEmpty = 0;
                    }

                    if(data.isTileEmpty && TStats[selectedBut-1][0].cost<=money){
                        placedTowers.emplace_back(towerTexture[selectedBut-1].towerTexture, mapMan1.getRealPos(data.tilePos), TStats[selectedBut-1], selectedBut);
                        money -= TStats[selectedBut-1][0].cost;
                    }
                }
                selectedBut = 0;
                selectedTower = 0;
            } else {
                
                // Kuleyi seçme
                for(int x=1; x<=placedTowers.size(); x++){
                    if(CheckCollisionPointRec(mousePos, placedTowers[x-1].getRec())){
                        selectedTower = x;
                        selectedTData = 1;
                        continue;
                    }
                }

                // Kule geliştime 
                if(selectedTower!=0 && !placedTowers[selectedTower-1].isInMaxLevel()){
                    towerStats newS = placedTowers[selectedTower-1].getNextStats();

                    if(towerUpdateButton.isClicked(mousePos) && newS.cost<=money){
                        placedTowers[selectedTower-1].updateLevel();
                        money -= newS.cost;
                    } else if (selectedTData==1){
                        selectedTData = 1;
                    } else {
                        selectedTData = 0;
                    }
                }

                // Kule Silme
                if(towerRemoveButton.isClicked(mousePos)){
                    money += placedTowers[selectedTower-1].getStats().cost / 2;

                    placedTowers[selectedTower-1].kill();
                    selectedTower = 0;
                }

                if(!selectedTData) selectedTower = 0;
                
            }


            // Butondan towerı koymak için seçme
            for(int x=1; x<=towerButtons.size(); x++){
                if(towerButtons[x-1].isClicked(mousePos)){
                    if(selectedBut==x){
                        selectedBut = 0;
                    } else {
                        selectedBut = x;
                    }
                }
            }

            // Durdurma başlatma
            if(waweBut.isClicked(mousePos) && waweIsReady){
                currentWawe++;
                waweIsReady = waweIsReady;
                //waweIsReady=!waweIsReady;
            }
        }
    }
    
    CloseWindow();
    return 0;
}