#pragma once

#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Level.h"
#include "Player.h"

bool isInsideMap(int x, int y);
void displayMap(Player& player, Level& level, int currentLevel);