#pragma once

#include "Player.h"

class Rogue : public Player
{
public:
    Rogue();

    void Displaystat() const override;
};