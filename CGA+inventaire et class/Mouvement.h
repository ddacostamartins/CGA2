#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Level.h"
#include "Player.h"

bool canMoveTo(const Level& level, int x, int y,
    int ignoredEnemy = -1,
    bool isHero = false);
bool movementhero(Player& player, Level& level);
void enemymovement(Level& level);