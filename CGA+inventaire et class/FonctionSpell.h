#pragma once
#include "Level.h"
#include "Player.h"

bool isEnemyAt(Level& level, int x, int y);
bool canDisplaySpellZone(Level& level, Player& player, int x, int y);
void displaySpellZone(int x, int y);
void displaySpellCursor();