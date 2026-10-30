#pragma once

#include "Player.h"

class Guerrier : public Player
{
public:
    Guerrier();

    void Displaystat() const override;
};