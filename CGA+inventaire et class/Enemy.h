#pragma once
#include "Entity.h"

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
};