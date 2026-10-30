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
    int MaxLife;

    Weapon weapon;
    Armors armor;

public:
    Player(int life, int damage, int armorValue, int maxLife = 20);

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
};