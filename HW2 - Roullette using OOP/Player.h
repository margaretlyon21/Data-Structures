#ifndef PLAYER_H
#define PLAYER_H

#include "Wheel.h"

class Player 
{
    public:
        Player(int startingMoney, int slots = 10);
        int spinOurWheel();
        int getMoney() { return money; }
        void setMoney(int newMoney) { money += newMoney; }
    private:
        Wheel ourWheel;
        int money;
};


#endif