#pragma once

#include "Warrior.h"
#include "Mage.h"
#include "Spell.h"

class WarriorMage : public Warrior, public Mage
{
public:
    WarriorMage();
    
    const char* GetName()
    {
        return "Warrior-Mage";
    }

    bool CanCastSpell() const override
    {
        return true;
    }
};