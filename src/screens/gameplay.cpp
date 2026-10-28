#include "screens/gameplay.hpp"

void gameplayScreen::start(){
    TraceLog(LOG_INFO, "MAIN BASLADI");
}
void gameplayScreen::loop(){
    ehBar.setActive(0);
    endStatus = 1;

    frameTime = GetFrameTime() * GData->gameSpeed; // Frame arası süre
    TimeAsFrame += frameTime;   // Geçen frame sayısı


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
                        bool isMult = 0, isSlow = 0;

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
}

void gameplayScreen::draw(){
    //* --------------------------- ÇİZİM BAŞLADI ---------------------------------------
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
                if (enemy.getActive()){
                    enemy.draw();
                    EnemyStats s = enemy.getStats();
                    bool hasHealthBar = std::find(s.specials.begin(), s.specials.end(), ES_BOSS) != s.specials.end();

                    if(hasHealthBar){
                        ehBar.setActive(1);
                        ehBar.setMaxHealth(s.maxHealth);
                        ehBar.setPos(Vector2Add(enemy.getPos(), {-10,-30}));

                        ehBar.draw(s.health);
                    }
                }
            }

        EndMode2D();
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