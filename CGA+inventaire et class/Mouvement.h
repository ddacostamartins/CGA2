#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Level.h"
#include "Player.h"

bool movePlayer(Player& player, Level& level, int key);
bool moveSpellTarget(Player& player, int key);
bool startSpellTargeting(Player& player);
bool handleEscape();