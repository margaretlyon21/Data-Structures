#ifndef HARDMODE_H
#define HARDMODE_H

#include "Wheel.h"

class HardMode : public Wheel {
public:
    HardMode(int newSlots);
    void adjustWheel(bool houseWin);
    int spinWheel();
};

#endif 