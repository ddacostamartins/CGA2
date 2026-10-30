#include "Player.h"

#include <algorithm>
#include <string>

Player::Player(int life, int damage, int armorValue, int maxLife)
    : Life(life),
    Damage(damage),
    Armor(armorValue),
    MaxLife(maxLife)
{
    if (MaxLife < 0)
        MaxLife = 0;

    if (Life < 0)
        Life = 0;

    if (Life > MaxLife)
        Life = MaxLife;

    if (Damage < 0)
        Damage = 0;

    if (Armor < 0)
        Armor = 0;
}

int Player::GetLife() const
{
    return Life;
}

void Player::SetLife(int value)
{
    if (value < 0)
        value = 0;

    if (value > MaxLife)
        value = MaxLife;

    Life = value;
}

int Player::GetDamage() const
{
    return Damage;
}

void Player::SetDamage(int value)
{
    if (value < 0)
        value = 0;

    Damage = value;
}

int Player::GetArmor() const
{
    return Armor;
}

void Player::SetArmor(int value)
{
    if (value < 0)
        value = 0;

    Armor = value;
}

int Player::GetTotalDamage() const
{
    return Damage + weapon.GetDamage();
}

void Player::SetTotalDamage(int value)
{
    if (value < 0)
        value = 0;

    Damage = value - weapon.GetDamage();

    if (Damage < 0)
        Damage = 0;
}

void Player::TakeDamage(int value)
{
    int attack = value - Armor - armor.GetDefense();

    if (attack < 0)
        attack = 0;

    SetLife(Life - attack);
}

void Player::Healing(int value)
{
    int heal = value + weapon.GetLifesteal();

    if (heal < 0)
        heal = 0;

    SetLife(Life + heal);
}

void Player::SetName(const std::string& value)
{
    Playername = value;
}

std::string Player::GetName() const
{
    return Playername;
}