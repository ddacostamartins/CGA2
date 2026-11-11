#pragma once

#include "Player.h"

class Warrior : public Player
{
public:
    Warrior();

    const char* GetName() 
    {
        return "Warrior";
    }
};