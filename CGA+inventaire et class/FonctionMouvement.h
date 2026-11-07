#pragma once

#include "Player.h"
#include "Level.h"

bool movePlayer(Player& player, Level& level, int key);
bool moveSpellTarget(Player& player, int key);
bool startSpellTargeting(Player& player);
bool handleEscape();