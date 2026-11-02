#pragma once

#include "Player.h"

class Warrior : public Player
{
public:
    Warrior();

    void Displaystat() const override;
};