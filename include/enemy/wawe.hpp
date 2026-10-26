
class wawe{
private:
    const float interval;
    float timeAsFrame;
    int towerType;
    int count;
    int waweNum;

    float savedClock = 0.f;
public:
    wawe(int waweNum, float timeAsFrame, int towerType, int count, float interval) : timeAsFrame(timeAsFrame), 
        towerType(towerType), count(count), interval(interval), waweNum(waweNum) {}

    float getInterval() const {return interval;};
    float getTimeAsFrame() const {return timeAsFrame;};
    int getTowerType() const {return towerType;};
    bool getActive() const {return count>0;};
    int getWawe() const {return this->waweNum;};

    void saveTime(float dt) {savedClock=dt;};
    float getSavedClock() const {return savedClock;};
    
    
    void countN() {count--;};
};
