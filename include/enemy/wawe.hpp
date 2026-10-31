#include <variant>

struct reward{
    int money;
};

class wawe{
private:
    const float interval;
    float timeAsFrame;
    int towerType;
    int count;
    
    float waweStartTime = 0.f;
    float savedClock = 0.f;
public:
    wawe(float timeAsFrame, int towerType, int count, float interval) : timeAsFrame(timeAsFrame), 
        towerType(towerType), count(count), interval(interval) {}

    float getInterval() const {return interval;};
    float getTimeAsFrame() const {return timeAsFrame;};
    int getTowerType() const {return towerType;};
    bool getActive() const {return count>0;};
    
    void setWaweStartTime(float dt) {waweStartTime=dt;};
    float getWaweStartTime() const {return waweStartTime;};

    void saveTime(float dt) {savedClock=dt;};
    float getSavedClock() const {return savedClock;};
    
    
    void countN() {count--;};
};

struct waweData {
    int waweNum;
    std::vector<wawe> usedWawes;
    reward waweReward;
    bool active = 1;
};