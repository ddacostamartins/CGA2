#pragma once

#include <string>

#include "Enemy.h"

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 10;
const int MAX_ENEMIES = 5;

class Exit {
public:
    std::string nom = "Exit";
    int x = 17;
    int y = 0;
};

class Level{
public:
    int Map[MAP_WIDTH * MAP_HEIGHT]{};

    Enemy enemies[MAX_ENEMIES]{};
    int enemyCount = 0;

    Exit sortie;

    int startX = 9;
    int startY = 0;
};

bool loadLevel(int numero, Level& level);