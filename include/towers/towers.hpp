#pragma once
#include <raylib.h>
#include <string>
#include <memory>
#include <vector>
#include "towers/bullet.hpp"
#include <iostream>


enum TowerType{
    T_NOTOWER, 
    T_TOWER1, 
    T_TOWER2, 
    T_TOWER3, 
    T_TOWER4,
    T_TOWER5
};

enum TowerSpecials{
    TS_NULL,
    TS_BOMB,
    TS_SLOW
};

enum TowerTarget{
    TARGET_NULL,
    
    TARGET_FIRST,
    TARGET_LAST,

    TARGET_SIZE
};

struct towerTexturesData{
    Texture2D buttonTexture;
    Texture2D towerTexture;
    Texture2D bulletTexture;
};


struct towerStats{
    float damage;
    float range;
    float attackSpeed;
    int cost;

    std::vector<TowerSpecial> specials;
    std::string data;
};

class tower1{
private:
    Vector2 pos{};
    const Texture2D* text;
    std::vector<towerStats> stats;
    int type;
    int level = 0;
    int maxLevel = 2;
    float dataBackup=0.f;
    bool active = 1;

    int targetSelect = TARGET_FIRST;
public:
    tower1(const Texture2D& text, Vector2 pos, std::vector<towerStats> stats, int type) : pos(pos), text(&text), stats(stats), type(type) {};
    ~tower1() = default;

    Vector2 getPos() const {return pos;};
    Vector2 getCenter() {return {pos.x+16, pos.y+16};};
    towerStats getStats() const {return stats[level];};
    towerStats getNextStats() const { return stats[level+1]; };
    int getType() const {return type;};
    int getLevel() const {return level;};
    Rectangle getRec() const {return {pos.x, pos.y, (float)text->width, (float)text->height};};
    bool getActive() const {return active;};
    int getTargetSelect() const {return targetSelect;};

    void setTarget(int x) {targetSelect = x;};
    void kill() {active=0;};

    
    void setTimer(float dt) {dataBackup = dt;};
    void updateLevel() {
        level++;
    };

    bool getBulletIsReady(float dt) {return dataBackup+stats[level].attackSpeed<=dt;};
    bool isInMaxLevel() const {return !(maxLevel>=level+1);};

    void draw();
    void drawEx(Vector2 pos);
};
