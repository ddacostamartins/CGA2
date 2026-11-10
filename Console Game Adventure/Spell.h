#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Levels.h"

// =========================
// CIBLAGE DU SORT
// =========================

extern bool spellConfirmed;
extern bool spellCancelled;
extern bool targetingSpell;

extern int targetX;
extern int targetY;

const int SPELL_RADIUS = 3;
const int SPELL_DAMAGE = 1;

void displaySpellTargeting(Level& level, Hero& hero);
void castSpell(Level& level);