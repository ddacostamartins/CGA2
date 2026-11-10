#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Levels.h"

bool isInsideMap(int x, int y);
void displayMap(const Hero& hero, const Level& level, int currentLevel);