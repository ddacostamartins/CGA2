#pragma once

#include <string>
#include "Armor.h"
#include "Weapon.h"

class Player
{
private:
    std::string Playername = "Default name";

protected:

    int Life;
    int Damage;
    int Armor;
    int Mana;
    int MaxLife;
    int Maxmana;
    int PlayerX;
    int PlayerY;

    Weapon weapon;
    Armors armor;

public:

    virtual const char* GetClassName() const = 0;

    Player(int life, int damage, int armorValue, int mana, int positionX = 0, int positionY = 0, int maxLife = 20, int maxmana = 100);

    int GetLife() const;
    void SetLife(int value);

    int GetDamage() const;
    void SetDamage(int value);

    int GetArmor() const;
    void SetArmor(int value);

    int GetTotalDamage() const;
    void SetTotalDamage(int value);

    void TakeDamage(int value);
    void Healing(int value);

    void SetName(const std::string& value);
    std::string GetName() const;

    virtual ~Player() = default;
    virtual void Displaystat() const = 0;

    int GetMana() const;
    void SetMana(int value);

    int GetPlayerX() const;
    int GetPlayerY() const;

    void SetPlayerX(int value);
    void SetPlayerY(int value);

    virtual bool CanCastSpell() const
    {
        return false;
    }
};