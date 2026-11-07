#pragma once

void displayLevelTitle(int currentLevel);
void getTerrainAppearance(int cell, char& symbole, int& color);
void displayTerrain(int x, int y, Level& level);
void displayHero(Player& player, int x, int y);
void displayExit(Level& level, int x, int y);
void displayEnemies(Level& level, int x, int y);