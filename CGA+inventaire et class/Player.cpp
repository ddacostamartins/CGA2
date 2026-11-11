#include "Player.h"
#include "Map.h"
#include "Attack.h"
#include "Mouvement.h"
#include "Spell.h"

Player::Player(int life, int damage, int armorValue,
    int mana, int playerX, int playerY,
    int maxLife, int maxmana)

    : Entity("Default name", life,damage, maxLife, playerX, playerY),
    Armor(armorValue),
    Mana(mana),
    Maxmana(maxmana)
{
    

    if (Armor < 0)
        Armor = 0;

    if (Mana < 0)
        Mana = 0;

    if (Maxmana < 0)
        Maxmana = 0;

    if (Mana > Maxmana)
        Mana = Maxmana;
}

bool Mage::movementhero(Player& player, Level& level)
{
    int key = getch();

    if (key == ERR)
        return false;

    if (key == 27)
        return handleEscape();

    if (key == 'e' || key == 'E')
        return startSpellTargeting(player);

    if (targetingSpell)
    {
        if (key == '\n' || key == '\r' || key == KEY_ENTER)
        {
            spellConfirmed = true;
            targetingSpell = false;
            return true;
        }

        return moveSpellTarget(player, key);
    }

    return movePlayer(player, level, key);
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