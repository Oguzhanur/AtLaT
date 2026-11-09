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
    inline std::vector<std::string> MainMenu = {"Main menu", "Ana Menü"};
    inline std::vector<std::string> Start = {"Start", "Başla"};
    inline std::vector<std::string> Settings = {"Settings", "Ayarlar"};
    inline std::vector<std::vector<std::string>> openClosed = {{"Open", "Closed"}, {"Açık", "Kapalı"}};

    //*------------------------- AYARLAR -----------------
    inline std::vector<std::vector<std::string>> settingsFullScreenButton = {{"Fullscreen", "Windowed"}, {"Tam Ekran", "Pencereli"}};
    inline std::vector<std::string> settingsFullScreenText = {"Fullscreen: ", "Tam ekran ayarı: "};

    inline std::vector<std::string> settingsLangagesText = {"Language: ", "Dil: "};

    //*------------------------- BÖLÜM SEÇME -----------------
    inline std::vector<std::string> gameselectSelectEpisode = {"Select episode", "Bölüm seçin"};

    //*------------------------- OYUN SONU -----------------
    inline std::vector<std::string> endRetry = {"Retry", "Tekrar dene"};
    inline std::vector<std::string> endWin = {"You win", "Kazandınnn"};
    inline std::vector<std::string> endLose = {"You lose", "Kaybettin"};
    inline std::vector<std::string> endEnd = {"Game Over", "Maç bitti"};

    //*------------------------- OYNANIŞ -----------------
    inline std::vector<std::string> BackToGame = {"Back to\n\ngame", "Oyuna Dön"};
    inline std::vector<std::string> InGameSettings = {"In game\n\nsettings", "Oyun içi\n\nayarlar"};
    inline std::vector<std::string> mainHealth = {"Base health: ", "Ana can: "};
    inline std::vector<std::string> enemyHealth = {"Enemy health: ", "Ana can: "};

    inline std::vector<std::string> maxLevel = {"Max Level", "Son Seviye"};

    inline std::vector<std::string> cost = {"Cost: ", "Maliyet: "};
    inline std::vector<std::string> money = {"Money: ", "Para: "};
    inline std::vector<std::string> wawe = {"Wave: ", "Wave: "};

    // Oyun içi ayarlar
    inline std::vector<std::string> gSetNoti = {"Notifications: ", "Bildirimler: "};
    inline std::vector<std::string> gSetDamageVis = {"Damage visibility: ", "Hasarları göster: "};
    inline std::vector<std::string> gSetSoundEffects = {"Sound effects: ", "Ses Efektleri: "};

    // Bildirimler
    inline std::vector<std::string> notiNotEnoghMoney = {"Not enough money!", "Yetersiz Para!"};
    inline std::vector<std::string> notiOnlyGrass = {"You can place\n\nonly grass", "Sadece toprağa\n\nkule koyabilirsin!"};
    inline std::vector<std::string> notiTowerDeleted = {"Tower deleted", "Kule silindi"};

    // Hedefler
    inline std::vector<std::string> target = {"Target: ", "Hedef: "};
    inline std::vector<std::string> targetNone = {"None", "Hiçbiri"};
    inline std::vector<std::string> targetFirst = {"First", "En Baştaki"};
    inline std::vector<std::string> targetLast = {"Last", "En Sonuncu"};
    inline std::vector<std::string> targetStrongest = {"Strongest", "En güçlü"};

    // Kule Geliştirmeleri
    inline std::vector<std::vector<std::vector<std::string>>> towersUpdates = {
        {{"Basic Tower", "Range Update", "Better guns"}, {"Basit Kule", "Geniş Alan", "Sağlam silah"}},

        {{"Strong & Slow tower", "Range Update", "Faster & Strong reload"}, {"Güçlü ama yavaş kule", "Geniş Alan", "Daha hızlı ve güçlü"}},

        {{"Range Attack Tower", "Strong bomb", "Mobile bomb"}, {"Alan Hasarlı kule", "Güçlü bombalar", "Daha efektif bomba"}},
        
        {{"Slowwer Tower", "Range Update", "Faster"}, {"Yavaşlatıcı kule", "Geniş Alan", "Daha hızlı"}}
    };

    // Kule ile ilgili
    inline std::vector<std::string> updateTower = {"Update\n\nTower", "Kuleyi\n\ngeliştir"};
    inline std::vector<std::string> deleteTower = {"Delete\n\nTower", "Kuleyi sil"};
    inline std::vector<std::string> changeTarget = {"Change\n\nTarget", "Hedefi\n\ndeğiştir"};
};
