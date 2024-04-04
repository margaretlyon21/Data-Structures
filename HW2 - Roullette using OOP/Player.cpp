#include <iostream>
#include <random>

#include "Player.h"

Player::Player(int startingMoney, int slots)
{
    money = startingMoney;
    ourWheel = Wheel(slots);
}

int Player::spinOurWheel()
{
    return ourWheel.spinWheel();
}

