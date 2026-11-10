#pragma once

#include "Player.h"

class Mage : public Player
{
public:
    Mage();

   

    const char* GetName() 
    {
        return "Mage";
    }

    bool CanCastSpell() const override
    {
        return true;
    }
};