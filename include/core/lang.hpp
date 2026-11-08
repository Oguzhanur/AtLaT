#pragma once
#include <string>
#include <vector>

enum LangType{
    LANG_EN,
    LANG_TR,


    LANG_END
};

namespace LANG{
    //*------------------------- GENEL -----------------
    inline std::vector<std::string> Language = {"English", "Türkçe"};
    inline std::vector<std::string> MainMenu = {"Main menu", "Ana menü"};
    inline std::vector<std::string> Start = {"Start", "Başla"};
    inline std::vector<std::string> Settings = {"Settings", "Ayarlar"};
    inline std::vector<std::vector<std::string>> openClosed = {{"Open", "Closed"}, {"Açık", "Kapalı"}};

    //*------------------------- AYARLAR -----------------
    inline std::vector<std::vector<std::string>> settingsFullScreenButton = {{"Fullscreen", "Windowed"}, {"Tam Ekran", "Pencereli"}};
    inline std::vector<std::string> settingsFullScreenText = {"Fullscreen: ", "Tam ekran ayarı: "};

    inline std::vector<std::string> settingsLangagesText = {"Select language: ", "Dil Ayarı: "};

    //*------------------------- BÖLÜM SEÇME -----------------
    inline std::vector<std::string> gameselectSelectEpisode = {"Select episode", "Bölüm seçin"};

    //*------------------------- OYUN SONU -----------------
    inline std::vector<std::string> endRetry = {"Retry", "Tekrar dene"};
    inline std::vector<std::string> endWin = {"You win", "Kazandınnn"};
    inline std::vector<std::string> endLose = {"You lose", "Kaybettin"};
    inline std::vector<std::string> endEnd = {"Game is ended", "Maç bitti"};

    //*------------------------- OYNANIŞ -----------------
    inline std::vector<std::string> BackToGame = {"Back to\n\ngame", "Oyuna Dön"};
    inline std::vector<std::string> InGameSettings = {"In game\n\nsettings", "Oyun içi\n\nayarlar"};
    inline std::vector<std::string> mainHealth = {"Main health: ", "Ana can: "};
    inline std::vector<std::string> enemyHealth = {"Main health: ", "Ana can: "};

    inline std::vector<std::string> maxLevel = {"MAX Level", "Son Seviye"};

    inline std::vector<std::string> cost = {"Cost: ", "Maaliyet: "};
    inline std::vector<std::string> money = {"Money: ", "Para: "};
    inline std::vector<std::string> wawe = {"Wawe: ", "Wawe: "};

    // Oyun içi ayarlar
    inline std::vector<std::string> gSetNoti = {"Notication: ", "Bildirimler: "};
    inline std::vector<std::string> gSetDamageVis = {"Damage visibilty: ", "Hasarları göster: "};
    inline std::vector<std::string> gSetSoundEffects = {"Sound effects: ", "Ses Efektleri: "};

    // Bildirimler
    inline std::vector<std::string> notiNotEnoghMoney = {"Not enough money!", "Yetersiz Para!"};
    inline std::vector<std::string> notiOnlyGrass = {"You can place\n\nonly grass", "Sadece toprağa\n\nkule koyabilirsin!"};
    inline std::vector<std::string> notiTowerDeleted = {"Tower deleted", "Kule silindi"};

    // Hedefler
    inline std::vector<std::string> target = {"Target: ", "Hedef: "};
    inline std::vector<std::string> targetNone = {"None", "Hiçbiri"};
    inline std::vector<std::string> targetFirst = {"First", "Baştaki"};
    inline std::vector<std::string> targetLast = {"Last", "Sonuncu"};
    inline std::vector<std::string> targetStrongest = {"Strongest", "En güçlü"};
};
