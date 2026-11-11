#pragma once
#include "Entity.h"
#include "Level.h"
#include "Map.h"

class Enemy : public Entity
{
protected:

public:
    
    Enemy()
        : Entity("Enemy", 0, 0, 0, 0, 0) 
    {
    }

    Enemy(int life, int damage, int positionX = 0, int positionY = 0,
        int maxLife = 20);

    void TakeDamage(int value);

    bool canMoveTo(const Level& level, int x, int y,
        int ignoredEnemy = -1,
        bool isHero = false);
    bool movementhero(Player& player, Level& level);
    void enemymovement(Level& level);
};