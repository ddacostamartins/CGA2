#pragma once
#include "Entity.h"

class Enemy : public Entity
{
protected:
    

public:

    Enemy(int life, int damage, int positionX = 0, int positionY = 0,
        int maxLife = 20);

    virtual const char* GetClassName() const = 0;

    virtual ~Enemy() = default;

    virtual void Displaystat() const = 0;


    void TakeDamage(int value);

    int GetPlayerX() const;
    int GetPlayerY() const;

    void SetPlayerX(int value);
    void SetPlayerY(int value);
};