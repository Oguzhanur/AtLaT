#include "screens/base.hpp"


class gameplayScreen : public baseScreen{
private:
    int money = 999;
    float baseHealth = 100.f;

    // Map ve seçme değişkenleri
    mapMan mapMan1;
    float frameTime = 0.f;
    float TimeAsFrame = 0.f;
    int selectedBut = 0;
    int selectedTower = 0;
    int selectedTData = 0;

    // ARAYÜZ
    Color BColor{0,100,0,100};
    gui::texture towerInfoMenu, rightMenu;
    Texture2D tUpdateM, tDeleteM, startButtonM, stopButtonM;
    gui::button towerUpdateButton, towerRemoveButton;
    gui::switchButton waweBut;
    gui::font mainFont, smallFont;
    healthBar hBar, ehBar;

    // OYNANIŞ
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
            { 2.f, 200.f, 1.0f, 100, {TS_SLOW}},
            { 2.f, 300.f, 0.5f, 100, {TS_SLOW}}}
    };

    std::vector<EnemyStats> eStats = { //? Maksimum can, can, hız
        // LVL 1
        { 25.f,  25.f, 100.f, {ES_NULL}}, // Normal düşman
        { 10.f,  10.f, 200.f, {ES_NULL}}, // Hızlı düşman
        {100.f, 100.f,  50.f, {ES_NULL}}, // Yavaş/Güçlü düşman
        // LVL 2
        {  30.f,   30.f,  350.f, {ES_NULL}},// Çok hızlı / Hafif güçlü
        { 100.f,  100.f,  200.f, {ES_NULL}}, // Orta hızlı / Çok güçlü
        {1000.f, 1000.f,  100.f, {ES_BOSS}}  // Boss fight
    };

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
    std::vector<wawe> wawes{ //? Olduğu Wawe / Wawe başlayınca geçen süre / Kule / Sayısı / Aralık
        {0, 1.f , E_LBoss, 1, 0.1},
        {1, 1.f , E_Speed, 10, 0.1},
        {1, 1.f , E_Normal, 5, .5},
        {2, 1.f , E_Speed, 50, 0.1},
        {2, 1.f , E_Normal, 10, 1},
        {2, 1.f , E_Heavy, 50, 0.5},
        {3, 1.f , E_Normal, 100, 0.01},
        {3, 3.f , E_Normal, 250, 0.01}
    };


public:
    gameplayScreen(ctx* GData) : baseScreen(GData),
        towerInfoMenu("data/gui/towerInfoMenu.png", {0,125}),
        tUpdateM(LoadTexture("data/gui/towerUpgrade.png")),
        tDeleteM(LoadTexture("data/gui/towerRemove.png")),
        towerUpdateButton(tUpdateM, {20,550}),
        towerRemoveButton(tDeleteM, {20,675}),
        startButtonM(LoadTexture("data/gui/startButton.png")),
        stopButtonM(LoadTexture("data/gui/stopButton.png")),
        waweBut(startButtonM, stopButtonM, {1000,550}),
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
            towerButtons.push_back(gui::button(towerTexture[x].buttonTexture, {1000.f + 100.f * (x/2), 100.f * (x%2)}));}

        // LVL 1
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemy.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemySpeed.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl1/enemyHeavy.png"));
        // LVL 2
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemyLight.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemyHeavy.png"));
        enemyTextures.push_back(LoadTexture("data/enemys/lvl2/enemyBoss.png"));
    }

    ~gameplayScreen() override {
        // TODO: tüm görsel içeren veriler vector içinde olsun ve o şekilde bellekten sil
        UnloadTexture(tUpdateM);
        UnloadTexture(tDeleteM);
        UnloadTexture(startButtonM);
        UnloadTexture(stopButtonM);

    }

    void start() override;
    void loop() override;
    void draw() override;
};