#pragma once

#include <string>

const int MAP_WIDTH = 20;
const int MAP_HEIGHT = 10;
const int MAX_ENEMIES = 5;

//enum class HeroState {
//    Idle,       // Le héros attend
//    Moving,     // Le héros se déplace
//    Casting,    // Le héros lance un sort
//    Dead        // Le héros est mort
//};

struct Hero {
    std::string nom = "Hero";
    int Life = 3;
    int x = 9;
    int y = 0;
};

struct Exit {
    std::string nom = "Exit";
    int x = 17;
    int y = 0;
};

struct Enemy {
    std::string nom = "Enemie";
    int Life = 2;
    int damage = 1;
    int x = 0;
    int y = 0;
};

struct Level {
    int Map[MAP_WIDTH * MAP_HEIGHT]{};

    Enemy enemies[MAX_ENEMIES]{};
    int enemyCount = 0;

    Exit sortie;

    int startX = 9;
    int startY = 0;
};

bool loadLevel(int numero, Level& level);