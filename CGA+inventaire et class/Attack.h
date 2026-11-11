#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Level.h"
#include "Player.h"

void enemyattack(Player& player, const Level& level);
void playerAttack(Player& player, Level& level, int enemyIndex);