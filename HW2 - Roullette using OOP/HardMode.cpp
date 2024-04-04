#include "HardMode.h"
#include <random>
#include <iostream>

HardMode::HardMode(int newSlots) : Wheel(newSlots) {}

int HardMode::spinWheel() {
    return rand() % getSlots() + 1; // Implement spinWheel for HardModeWheel
}

//function to adjust the number of slots on the houses wheel 
void HardMode::adjustWheel(bool playerwin) {
    //checks if house won this time
    if (!playerwin) {
        //checks if house won last time
        if (getLastHouseWin()){
            //decrements if house won twice in a row and the minimum has not been reached
            int newslots = getSlots() - 1;
            if (newslots > 6){
                setSlots(-1);
            }
        }
    } else {
        //increments slots if player won 
        setSlots(1);
    }
    setLastHouseWin(!playerwin);
}