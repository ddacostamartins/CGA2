#pragma once

#include "Player.h"

class WarriorMage : public Player
{
public:
    WarriorMage();

   

    const char* GetName()
    {
        return "Guerrier-Mage";
    }

    bool CanCastSpell() const override
    {
        return true;
    }
};