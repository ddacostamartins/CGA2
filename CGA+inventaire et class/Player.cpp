#include "Player.h"
#include "Map.h"
#include "Attack.h"

Player::Player(int life, int damage, int armorValue,
    int mana, int playerX, int playerY,
    int maxLife, int maxmana)

    : Entity("Default name", life, maxLife, playerX, playerY),
    Damage(damage),
    Armor(armorValue),
    Mana(mana),
    Maxmana(maxmana)
{
    if (Damage < 0)
        Damage = 0;

    if (Armor < 0)
        Armor = 0;

    if (Mana < 0)
        Mana = 0;

    if (Maxmana < 0)
        Maxmana = 0;

    if (Mana > Maxmana)
        Mana = Maxmana;
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

    SetLife(GetLife() - attack);
}

void Player::Healing(int value)
{
    int heal = value + weapon.GetLifesteal();

    if (heal < 0)
        heal = 0;

    SetLife(GetLife() + heal);
}

int Player::GetMana() const
{
    return Mana;
}

void Player::SetMana(int value)
{
    if (value < 0)
        value = 0;

    if (value > Maxmana)
        value = Maxmana;

    Mana = value;
}

int Player::GetPlayerX() const
{
    return GetPositionX();
}

void Player::SetPlayerX(int value)
{
    if (value < 0)
        value = 0;

    if (value >= MAP_WIDTH)
        value = MAP_WIDTH - 1;

    SetPositionX(value);
}

int Player::GetPlayerY() const
{
    return GetPositionY();
}

void Player::SetPlayerY(int value)
{
    if (value < 0)
        value = 0;

    if (value >= MAP_HEIGHT)
        value = MAP_HEIGHT - 1;

    SetPositionY(value);
}