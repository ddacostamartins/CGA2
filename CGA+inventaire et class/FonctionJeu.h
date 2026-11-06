#pragma once
#include "Level.h"
#include "Player.h"

void initialiserJeu();
bool initialiserNiveau(int currentLevel, Level& level, Player& player);
void tourEnnemis(Player& player, Level& level);
void gererCiblageSort(Player& player, Level& level, int currentLevel);
bool changerNiveau(int& currentLevel, Level& level, Player& player);
bool gererDeplacement(Player& player, Level& level, int& currentLevel);