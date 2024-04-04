#ifndef WHEEL_H
#define WHEEL_H

class Wheel 
{
    public:
        Wheel(int slots = 10);
        void setSlots(int newSlots) {slots += newSlots;}
        int getSlots(){return slots;}
        void setLastHouseWin(bool houseWin) {LastHouseWin = houseWin;}
        bool getLastHouseWin(){return LastHouseWin;}
        int spinWheel();
    private:
        int slots;
        bool LastHouseWin;
};


#endif