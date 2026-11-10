#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Levels.h"

bool canMoveTo(const Level& level, int x, int y,
    int ignoredEnemy = -1,
    bool isHero = false);
bool movementhero(Hero& hero, const Level& level);
void enemymovement(Level& level);