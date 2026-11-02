#pragma once

#include "Player.h"

class WarriorMage : public Player
{
public:
    WarriorMage();

    void Displaystat() const override;
};