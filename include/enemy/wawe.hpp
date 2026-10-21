
class wawe{
private:
    int timeAsFrame;
    int towerType;
    int count;
public:
    wawe(int timeAsFrame, int towerType, int count) : timeAsFrame(timeAsFrame), towerType(towerType), count(count) {}

    int getTimeAsFrame() const {return timeAsFrame;};
    int getTowerType() const {return towerType;};
    bool getActive() const {return count>0;};
    
    void countN() {count--;};
};
