#pragma once
#include "screens/base.hpp"


class gameplayScreen : public baseScreen{
private:
    int moneyEarnData = 500;
    int money = 500;
    float baseHealth = 100.f;

    // Map ve seçme değişkenleri
    mapMan mapMan1;
    float frameTime = 0.f;
    float TimeAsFrame = 0.f;
    int selectedBut = 0;
    int selectedTower = 0;
    int selectedTData = 0;

    // DEBUG
    bool DEBUG_TOWERDATAS = 1;
    bool DEBUG_WAWESTART = 1;

    // ARAYÜZ
    Color BColor{0,100,0,100};
    gui::texture towerInfoMenu, rightMenu;
    Texture2D tUpdateM, tDeleteM, startButtonM, stopButtonM, tChangeM, timedBomb64x64;
    gui::button towerUpdateButton, towerRemoveButton, towerTargetButton;
    gui::switchButton waweBut;
    gui::font mainFont, smallFont;
    healthBar hBar, ehBar;

    // OYNANIŞ
    std::vector<std::vector<towerStats>> TStats = { //? Hasar, Alan, Saldırı Hızı, Maliyet
        {   { 1.f, 150.f, 0.5f, 250, {{TS_NULL}}, "Basic Tower"}, // Normal
            { 1.f, 200.f, 0.5f, 100, {{TS_NULL}}, "Range Update"}, 
            { 2.f, 200.f, 0.3f, 300, {{TS_NULL}}, "Better guns"}},

        {   { 4.f, 250.f, 2.0f, 450, {{TS_NULL}}, "Strong & Slow tower"}, // yavaş ve güçlü
            { 4.f, 400.f, 2.0f, 120, {{TS_NULL}}, "Range Update"},
            { 8.f, 400.f, 1.0f, 400, {{TS_NULL}}, "Faster & Strong reload"}},

        {   { 4.f, 150.f, 4.0f, 350, {{TS_BOMB, 6}}, "Range Attack Tower"}, // Alan vuran, yavaş
            { 8.f, 150.f, 4.0f, 250, {{TS_BOMB, 6}}, "Strong bomb"},
            { 8.f, 200.f, 2.5f, 550, {{TS_BOMB, 6}}, "Mobile bomb"}},

        {   { 0.f, 150.f, 1.0f, 150, {{TS_SLOW, 3}}, "Slowwer Tower"}, // Yavaşlatan
            { 0.f, 300.f, 1.0f, 150, {{TS_SLOW, 3}}, "Range Update"},
            { 0.f, 300.f, 0.5f, 300, {{TS_SLOW, 5}}, "Faster"}}
    };

    std::vector<EnemyStats> eStats = { //? Maksimum can, can, hız
        {  4.f,   4.f, 150.f, {ES_NULL}}, // Normal düşman
        {  2.f,   2.f, 250.f, {ES_NULL}}, // Hızlı düşman
        { 10.f,  10.f, 100.f, {ES_NULL}}, // Yavaş/Güçlü düşman
        {150.f, 150.f, 150.f, {ES_BOSS}}, // Güçlü


        // LVL 2
        { 150.f,  150.f,  350.f, {ES_NULL}},// Çok hızlı / Hafif güçlü
        { 300.f,  300.f,  200.f, {ES_NULL}}, // Orta hızlı / Çok güçlü
        {2500.f, 2500.f,  100.f, {ES_BOSS}}  // Boss fight
    };

    std::vector<gui::timedTexture> timedTextures;
    std::vector<towerTexturesData> towerTexture;
    std::vector<gui::button> towerButtons;
    std::vector<Texture2D> enemyTextures;
    std::vector<tower1> placedTowers;
    std::vector<enemys> enemysComming;
    std::vector<Bullet> bullets;

    towerTexturesData t1,t2, t3,t4;

    // Wawe
    int endStatus = 0;
    int currentWawe = 0;
    bool waweIsReady = 1;
    std::vector<waweData> waweDatas{
        // LVL 1 (DPS/COST = EASY:60, NORMAL:50 HARD:40)
        // LVL 1 (DPS-ATTACK = EASY:3, NORMAL:4 HARD:5)
        {1, {wawe{1.f, E_Normal, 7, 1.}}, reward{50}}, // START: 500

        {2, {wawe{1.f, E_Normal, 10, .5}}, reward{25}},

        {3, {wawe{1.5f, E_Speed, 10, .5}}, reward{50}},

        {4, {wawe{1.f, E_Heavy, 10, 1.}}, reward{100}},

        {5, {wawe{1.f, E_Normal, 10, 1.}, 
             wawe{1.f, E_Speed, 10, 1.}, 
             wawe{1.f, E_Heavy, 10, 1.}}, reward{150}},
        
        {6, {wawe{1.f, E_Heavy, 10, 1.},
             wawe{1.f, E_Speed, 20, .5}}, reward{100}},

        {7, {wawe{1.f, E_Heavy, 20, .5}}, reward{100}},

        {8, {wawe{1.f, E_Heavy, 20, .2},
             wawe{3.f, E_Speed, 20, .3}}, reward{100}},

        {9, {wawe{1.5f, E_Speed, 25, .5},
             wawe{12.f, E_Normal, 20, .5}}, reward{200}},

        {10, {wawe{1.f, E_Normal, 10, 0.5},
             wawe{1.f, E_Speed, 10, 0.5},
             wawe{3.f, E_Boss, 1, 1.}}, reward{250}}
    };



public:
    gameplayScreen(ctx* GData) : baseScreen(GData),
        towerInfoMenu("data/gui/towerInfoMenu.png", {0,125}),
        timedBomb64x64(LoadTexture("data/gui/bomb64x64.png")),
        tUpdateM(LoadTexture("data/gui/towerUpgrade.png")),
        tDeleteM(LoadTexture("data/gui/towerRemove.png")),
        tChangeM(LoadTexture("data/gui/towerChange.png")),
        towerUpdateButton(tUpdateM, {20, 550}),
        towerRemoveButton(tDeleteM, {20, 675}),
        towerTargetButton(tChangeM, {20, 350}),
        startButtonM(LoadTexture("data/gui/startButton.png")),
        stopButtonM(LoadTexture("data/gui/stopButton.png")),
        waweBut(startButtonM, stopButtonM, {1000,700}),
        rightMenu("data/gui/RMenu.png", {1000,0}),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        smallFont("data/font/Bungee-Regular.ttf", 24.f),
        hBar({20,20}, {400,50}, 10.f, baseHealth, "Health: ", 1),
        ehBar({500,20}, {84,20}, 3.f, 0.f, "Enemy health: ", 0)
    {
        camera.target = {GData->ScreenSize.x/2, GData->ScreenSize.y/2};
        camera.offset = {GData->ScreenSize.x/2, GData->ScreenSize.y/2};

        // ---------------- KULE VERİLERİ -----------------
        towerTexture.reserve(4);

        towerTexture.push_back({
            LoadTexture("data/items/item1But.png"),
            LoadTexture("data/items/item1.png"),
            LoadTexture("data/items/item1Bul.png")
        });

        towerTexture.push_back({
            LoadTexture("data/items/item2But.png"),
            LoadTexture("data/items/item2.png"),
            LoadTexture("data/items/item2Bul.png")
        });

        towerTexture.push_back({
            LoadTexture("data/items/item3But.png"),
            LoadTexture("data/items/item3.png"),
            LoadTexture("data/items/item3Bul.png")
        });
        
        towerTexture.push_back({
            LoadTexture("data/items/item4But.png"),
            LoadTexture("data/items/item4.png"),
            LoadTexture("data/items/item4Bul.png")
        });

        for(int x=0; x<towerTexture.size(); x++){
            towerButtons.push_back(gui::button(towerTexture[x].buttonTexture, {1000.f + 100.f * (x/2), 120.f * (x%2)}));}

        // LVL 1
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemy.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemySpeed.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemyHeavy.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemyBoss.png"));
        // LVL 2
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemyLight.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemyHeavy.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemyBoss.png"));
    }

    ~gameplayScreen() override {
        // TODO: tüm görsel içeren veriler vector içinde olsun ve o şekilde bellekten sil
        UnloadTexture(tUpdateM);
        UnloadTexture(tDeleteM);
        UnloadTexture(tChangeM);
        UnloadTexture(startButtonM);
        UnloadTexture(stopButtonM);

    }

    void start() override;
    void loop() override;
    void draw() override;
};