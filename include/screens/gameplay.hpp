#pragma once
#include "screens/base.hpp"
#include <algorithm>

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

    // Ayarlar
    bool settingsScreen = 0;
    bool SET_Noti=1;
    bool SET_DamageVis=1;
    bool SET_Sounds=1;
    
    int testtt=0;
    bool playSound = 1;

    // DEBUG
    bool DEBUG_TOWERDATAS = 1;
    bool DEBUG_WAWESTART = 1;

    // ARAYÜZ
    Color BColor{0,100,0,100};
    gui::texture towerInfoMenu, rightMenu, settingsMenu;
    Texture2D tUpdateM, tDeleteM,startButtonM, stopButtonM, tChangeM, timedBomb64x64, button200x100Text, button200x80Text, hiddenBut, notificationText, notificationDamageText;
    gui::button towerUpdateButton, towerRemoveButton, towerTargetButton;
    gui::textButton settingsButton, settingsExit, settingsToMenu;
    gui::switchTextButton settingsNoti, settingsDamageVis, settingsSoundEffects;
    gui::switchButton waweBut;
    gui::font megaFont, mainFont, smallFont;
    healthBar hBar, ehBar;

    // SESLER
    soundsEffect damageEffect;

    // OYNANIŞ
    std::vector<gui::timedTexture> timedTextures;
    std::vector<towerTexturesData> towerTexture;
    std::vector<gui::hiddenButton> towerButtons;
    std::vector<Texture2D> enemyTextures;
    std::vector<tower1> placedTowers;
    std::vector<enemys> enemysComming;
    std::vector<Bullet> bullets;
    notification* mainNotification = nullptr;
    std::vector<notification*> damageNotifications;

    std::vector<AllWawesData> waweDatas;
    std::vector<EnemyStats> eStats;
    std::vector<std::vector<towerStats>> TStats;

    towerTexturesData t1,t2, t3,t4;

    // Wawe
    int endStatus = 0;
    int currentWawe = 0;
    bool waweIsReady = 1;
public:
    gameplayScreen(ctx* GData) : baseScreen(GData),
        towerInfoMenu("data/gui/towerInfoMenu.png", {0,120}),
        rightMenu("data/gui/RMenu.png", {1080,0}),
        settingsMenu("data/gui/settingsScreen.png", {100,100}),
        timedBomb64x64(LoadTexture("data/gui/bomb64x64.png")),
        tUpdateM(LoadTexture("data/gui/towerUpgrade.png")),
        tDeleteM(LoadTexture("data/gui/towerRemove.png")),
        tChangeM(LoadTexture("data/gui/towerChange.png")),
        button200x100Text(LoadTexture("data/gui/buttons/button200x100.png")),
        button200x80Text(LoadTexture("data/gui/buttons/button200x80.png")),
        towerUpdateButton(tUpdateM, {20, 495}),
        towerRemoveButton(tDeleteM, {20, 605}),
        towerTargetButton(tChangeM, {20, 345}),

        settingsExit(button200x100Text, LANG::BackToGame[GData->lang], mainFont, BLACK, {980,100}),
        settingsToMenu(button200x100Text, LANG::MainMenu[GData->lang], mainFont, BLACK, {100,100}),
        settingsNoti(button200x80Text, LANG::openClosed[GData->lang], mainFont, BLACK, {880,210}),
        settingsDamageVis(button200x80Text, LANG::openClosed[GData->lang], mainFont, BLACK, {880,310}),
        settingsSoundEffects(button200x80Text, LANG::openClosed[GData->lang], mainFont, BLACK, {880,410}),
        
        startButtonM(LoadTexture("data/gui/startButton.png")),
        stopButtonM(LoadTexture("data/gui/stopButton.png")),
        settingsButton(button200x100Text, LANG::InGameSettings[GData->lang], mainFont, BLACK, {1080, 450}),
        waweBut(startButtonM, stopButtonM, {1080,620}),
        megaFont("data/font/Bungee-Regular.ttf", 64.f),
        mainFont("data/font/Bungee-Regular.ttf", 32.f),
        smallFont("data/font/Bungee-Regular.ttf", 24.f),
        hBar({20,20}, {400,50}, 10.f, baseHealth, LANG::mainHealth[GData->lang], 1),
        ehBar({500,20}, {84,20}, 3.f, 0.f, LANG::enemyHealth[GData->lang], 0),
        hiddenBut(LoadTexture("data/items/hiddenBut.png")),
        notificationText(LoadTexture("data/gui/notification.png")),
        notificationDamageText(LoadTexture("data/gui/damageInfo.png")),
        waweDatas(data::waweDatas),
        eStats(data::eStats),
        TStats(data::TStats),
        damageEffect("data/sounds/shoot.wav", 0.1)
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
            bool outActive = 0;
            for(int haved : GData->havedTowerList){
                if(haved == x){
                    outActive = 1;
                    break;
                }
            }
            towerButtons.push_back(gui::hiddenButton(towerTexture[x].buttonTexture, hiddenBut, {1080.f + 100.f * (x/2), 120.f * (x%2)}, outActive));
        }

        // LVL 1
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemy.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemySpeed.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemyHeavy.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemyBoss.png"));
        // LVL 2
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemy.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemySpeed.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemyHeavy.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemyLight.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemyStorm.png"));
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