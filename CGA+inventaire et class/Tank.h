#pragma once

#include "Player.h"

class Tank : public Player
{
public:
    Tank();

    void Displaystat() const override;
};