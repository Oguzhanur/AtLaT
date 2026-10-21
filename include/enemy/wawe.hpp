
class wawe{
private:
    float timeAsFrame;
    int towerType;
    int count;
public:
    wawe(float timeAsFrame, int towerType, int count) : timeAsFrame(timeAsFrame), towerType(towerType), count(count) {}

    float getTimeAsFrame() const {return timeAsFrame;};
    int getTowerType() const {return towerType;};
    bool getActive() const {return count>0;};
    
    void countN() {count--;};
};
