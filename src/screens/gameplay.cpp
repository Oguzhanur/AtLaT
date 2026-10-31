#include "screens/gameplay.hpp"

void gameplayScreen::start(){
    TraceLog(LOG_INFO, "MAIN BASLADI");
}
void gameplayScreen::loop(){

    // -------------------------------- BUTONLAR VE TIKLAMA --------------------------------
    Vector2 mousePos = GetMousePosition();

    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)){
        selectedTData = 0;

        if(selectedBut!=0){
            // Kuleyi yerleştirme
            Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            TileData data = mapMan1.getTileByPos(worldPos);

            if(data.type==Tile_GRASS){
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

            // Kule hedef değiştirme
            if(selectedTower!=0 && placedTowers[selectedTower-1].getTargetSelect()!=TARGET_NULL){
                int targetType = placedTowers[selectedTower-1].getTargetSelect();

                if(towerTargetButton.isClicked(mousePos)){
                    if(targetType < TARGET_SIZE-1){
                        targetType++;
                    } else {
                        targetType=1;
                    }
                    placedTowers[selectedTower-1].setTarget(targetType);
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
                moneyEarnData += placedTowers[selectedTower-1].getStats().cost / 2;

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
    } else if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)){
        selectedBut = 0;
        selectedTower = 0;
    }

    
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


    Vector2 bombPos = {NULL_POS, NULL_POS};
    int bombValue = 0.f;

    for (Bullet& bul : bullets){
        if(bul.getActive()){ 
            std::vector<TowerSpecial> specials = bul.getSpecials();
            bul.updateBullet(frameTime);

            for (enemys& enemy : enemysComming){
                if (CheckCollisionPointCircle(enemy.getPos(), bul.getPos(), 32) && enemy.getActive()){
                    bul.killBullet();
                    enemy.attack(bul.getDamage());
                    money += bul.getDamage() * (0.5f * GData->hardness );
                    moneyEarnData += bul.getDamage() * (0.5f * GData->hardness );

                    // Özellikler
                    for(TowerSpecial& s : specials){
                        if(s.type == TS_BOMB){
                            bombPos = bul.getPos();
                            timedTextures.push_back(gui::timedTexture{timedBomb64x64, bombPos, .1f, TimeAsFrame});
                            bombValue = s.value;
                        } else if (s.type == TS_SLOW){
                            enemy.addEffect({EFFECT_SLOW, (float)s.value, 0.f});
                        }
                    }

                    break;
                }
            }
        }
    }

    // Bomba
    if(bombPos.x != NULL_POS && bombPos.y != NULL_POS){
        int x = 0;
        for (enemys& enemy : enemysComming){
            if (CheckCollisionPointCircle(enemy.getPos(), bombPos, 64) && enemy.getActive()){
                enemy.attack(bombValue);
                x++;

            }
        }

        TraceLog(LOG_INFO, "-------------------");
        bombPos = {NULL_POS, NULL_POS};
        bombValue = 0;
    }

    // --------------------------- KULE -------------------
    for (tower1& tower : placedTowers){
        if(!tower.getBulletIsReady(TimeAsFrame)) continue;

        const towerStats& stats = tower.getStats();
        Vector2* enemyPosPtr = nullptr;
        float enemyTakenPos = 0.f;
        float enemyHealth = 0.f;

        for (enemys& enemy : enemysComming){
            if (!enemy.getActive()) continue;

            if(CheckCollisionCircleRec(tower.getCenter(), stats.range, enemy.getRec())){
                switch (tower.getTargetSelect()){
                    case TARGET_NULL:
                        continue;

                    case TARGET_FIRST:
                        if(enemyPosPtr==nullptr || enemyTakenPos < enemy.getTakedPosFloat()){
                            enemyPosPtr = enemy.getPosPtr();
                            enemyTakenPos = enemy.getTakedPosFloat();
                            tower.setTimer(TimeAsFrame);
                        }
                        continue;

                    case TARGET_LAST:
                        if(enemyPosPtr==nullptr || enemyTakenPos > enemy.getTakedPosFloat()){
                            enemyPosPtr = enemy.getPosPtr();
                            enemyTakenPos = enemy.getTakedPosFloat();
                            tower.setTimer(TimeAsFrame);
                        }
                        continue;
                    
                    case TARGET_STRONG:
                        if(enemyPosPtr==nullptr || enemyHealth < enemy.getStats().health){
                            enemyPosPtr = enemy.getPosPtr();
                            enemyHealth = enemy.getStats().health;
                            tower.setTimer(TimeAsFrame);
                        }
                        
                        continue;
                }
            
            }
            
        }


        if(enemyPosPtr != nullptr){
            bullets.push_back(Bullet{towerTexture[tower.getType()-1].bulletTexture, tower.getCenter(), enemyPosPtr, 1500.f, stats.damage, tower.getStats().specials});
        }
    }

    //  DEBUGG
    if(GData->debugMode){
        if(DEBUG_WAWESTART){
            int wx = 0;
            int earnedMoney = money;
            int lastLevel = 0;
            for(waweData& wData : waweDatas){
                wx++;
                TraceLog(LOG_INFO, "Wawe %i Başlangıç parası: %i", wx, earnedMoney);

                for (wawe& w : wData.usedWawes){
                    earnedMoney += (eStats[w.getTowerType()-1].health * w.getCount());
                    earnedMoney += wData.waweReward.money;
                }
            }

            TraceLog(LOG_INFO, "----------------------");
            DEBUG_WAWESTART = 0;
        }
        if(DEBUG_TOWERDATAS){
            for (const auto& tower : TStats){
                TraceLog(LOG_INFO, "%s:", tower[0].data.c_str());
                int level = 0;
                int totalCost = 0;
                for(const auto& data : tower){
                    totalCost += data.cost;
                    
                    float dps = data.damage/data.attackSpeed;
                    float cost_dps = totalCost/dps;
                    float efficiens = (dps*data.range)/(150.f/5.f); // Range / Tahmini düşman hızı / 5.f

                    TraceLog(LOG_INFO, "  %i -> DPS: %f, Cost/DPS: %f, Tahmini Hasar:%f", level, dps, cost_dps, efficiens);
                    level++;
                }
            }

            TraceLog(LOG_INFO, "----------------------");
            DEBUG_TOWERDATAS = 0;
        }
    }

    waweIsReady = 1;
    for (waweData& wData : waweDatas){
        if(!wData.active) continue;
        bool anyWaweActive = 0;
        
        for (wawe& w : wData.usedWawes){
            if(!w.getActive()) continue;
            endStatus = 0;
            anyWaweActive = 1;

            if(currentWawe == wData.waweNum){
                if(w.getWaweStartTime()==0.f) w.setWaweStartTime(TimeAsFrame);
                waweIsReady = 0;

                if(TimeAsFrame>+w.getSavedClock()+w.getInterval() && TimeAsFrame > w.getWaweStartTime() + w.getTimeAsFrame()){
                    w.saveTime(TimeAsFrame);
                    enemysComming.emplace_back(enemyTextures[w.getTowerType()-1], Vector2{0, 192}, eStats[w.getTowerType()-1]);
                    w.countN();
                }
            }
        }
        if (currentWawe==wData.waweNum && !anyWaweActive){
            money += wData.waweReward.money;
            moneyEarnData += wData.waweReward.money;

            wData.active = 0;
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

    timedTextures.erase(
        std::remove_if(timedTextures.begin(), timedTextures.end(), [this](const gui::timedTexture& timedText) {return !timedText.getActive(TimeAsFrame);}), timedTextures.end()
    );
}

//* --------------------------- ÇİZİM BAŞLADI ---------------------------------------
void gameplayScreen::draw(){

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

        for (gui::timedTexture& timedText : timedTextures){
            if (timedText.getActive(TimeAsFrame)) timedText.draw();}

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
            gui::drawText(std::to_string(TStats[x-1][0].cost) + "$", Vector2Add(towerButtons[x-1].getPos(), {20,95}), smallFont, WHITE);
        }

        if(selectedTower!=0){
            DrawCircleV(placedTowers[selectedTower-1].getCenter(), placedTowers[selectedTower-1].getStats().range, BColor);
            
            towerInfoMenu.draw();
            towerStats s = placedTowers[selectedTower-1].getStats();
            float towerDps = s.damage/s.attackSpeed;
            if(GData->debugMode){
                gui::drawText("Attack Speed: " + gui::floatToStr(s.attackSpeed), {20,150}, smallFont, BLACK);
                gui::drawText("Damage: " + gui::floatToStr(s.damage), {20,180}, smallFont, BLACK);
                gui::drawText("Range: " + gui::floatToStr(s.range), {20,210}, smallFont, BLACK);
                gui::drawText("DPS: " + gui::floatToStr(towerDps), {20,240}, smallFont, BLACK);
                gui::drawText("Cost/DPS: " + gui::floatToStr((float)placedTowers[selectedTower-1].getTotalCost()/towerDps), {20,270}, smallFont, BLACK);

            }
            
            towerUpdateButton.draw();
            towerRemoveButton.draw();

            std::string targetText = " ";
            switch (placedTowers[selectedTower-1].getTargetSelect()){
                case TARGET_NULL:
                    targetText = "None";
                    break;
                case TARGET_FIRST:
                    targetText = "First";
                    break;
                case TARGET_LAST:
                    targetText = "Last";
                    break;
                case TARGET_STRONG:
                    targetText = "Strong";
                    break;
            };

            towerTargetButton.draw();
            gui::drawText("Target: " + targetText, {20, 320}, smallFont, BLACK);
            
            if(placedTowers[selectedTower-1].isInMaxLevel()){
                gui::drawText("MAX Level", {20,520}, smallFont, BLACK);
            } else {
                towerStats nextStats = placedTowers[selectedTower-1].getNextStats();

                gui::drawText(nextStats.data + ": ", {22,500}, smallFont, BLACK);
                gui::drawText("Cost: " + gui::floatToStr(nextStats.cost) + "$", {22,520}, smallFont, BLACK);
            }

        }


        hBar.draw(baseHealth);

        Vector2 hPos = hBar.getPos();
        Vector2 hSize = hBar.getSize();

        gui::drawText(hBar.getAsText(baseHealth), {hPos.x, hPos.y+hSize.y+10}, mainFont, WHITE);

        std::string moneyText = "Money: " + std::to_string(money);
        gui::drawText(moneyText, {800,20}, mainFont, Color{255,215,0,255});

        std::string waweText = "Wawe: " + std::to_string(currentWawe);
        gui::drawText(waweText, {1015, 670}, mainFont, BLACK);

        if(GData->debugMode){
            std::string totalEarnedMoneyText = "Earned Money: " + std::to_string(moneyEarnData);
            gui::drawText(totalEarnedMoneyText, {700,50}, mainFont, RED);
        }

        waweBut.draw(waweIsReady);

        if(endStatus==1){
            gui::drawText("GAME OVER: YOU WİN", {600, 100}, mainFont, GREEN);
            GData->isPlayerWinnedGame = 1;
            GData->status = SCREEN_END;
        } else if (endStatus==-1){
            gui::drawText("GAME OVER: YOU LOSE", {600, 100}, mainFont, RED);
            GData->isPlayerWinnedGame = 0;
            GData->status = SCREEN_END;
        }

    //* --------------------------- ÇİZİM BİTTİ ---------------------------------------
    

}