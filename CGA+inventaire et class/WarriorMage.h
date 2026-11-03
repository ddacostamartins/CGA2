#pragma once

#include "Player.h"

class WarriorMage : public Player
{
public:
    WarriorMage();

    void Displaystat() const override;

    const char* GetClassName() const override
    {
        return "Guerrier-Mage";
    }

    bool CanCastSpell() const override
    {
        return true;
    }
};