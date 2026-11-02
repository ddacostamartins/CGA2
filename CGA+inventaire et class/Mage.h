#pragma once

#include "Player.h"

class Mage : public Player
{
public:
    Mage();

    void Displaystat() const override;
};