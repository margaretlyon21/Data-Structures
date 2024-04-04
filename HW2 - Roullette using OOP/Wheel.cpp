#include <iostream>
#include <random>

#include "Wheel.h"

Wheel::Wheel(int newSlots)
{
    slots = newSlots;
}

int Wheel::spinWheel()
{
    return rand() % slots + 1;
}
