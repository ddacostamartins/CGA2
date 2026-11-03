#pragma once

#include "Player.h"

class Mage : public Player
{
public:
    Mage();

    void Displaystat() const override;

    const char* GetClassName() const override
    {
        return "Mage";
    }

    bool CanCastSpell() const override
    {
        return true;
    }
};