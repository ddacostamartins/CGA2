#pragma once

#include "Entity.h"
#include "Armor.h"
#include "Weapon.h"

class Player : public Entity
{
protected:

    int Armor;
    int Mana;
    int Maxmana;

    Weapon weapon;
    Armors armor;

public:

    Player(int life, int damage, int armorValue,
        int mana, int positionX = 0, int positionY = 0,
        int maxLife = 20, int maxmana = 100);

    

    

    


    int GetArmor() const;
    void SetArmor(int value);

    int GetTotalDamage() const;
    void SetTotalDamage(int value);

    void TakeDamage(int value);
    void Healing(int value);

    int GetMana() const;
    void SetMana(int value);


    virtual bool CanCastSpell() const
    {
        return false;
    }
};