#include <iostream>
#include "Mage.h"
#include "Mouvement.h"

Mage::Mage(int life, int damage, int armorValue, int mana, int playerX, int playerY, int maxLife, int maxmana, int targetX = 0, int targetY = 0)
    : Player(life, damage, armorValue, mana, playerX, playerY, maxLife, maxmana),
    TargetX(targetX),
    TargetY(targetY)
{
    if (TargetX < 0)
        TargetX = 0;

    if (TargetY < 0)
        TargetY = 0;
}

int Mage::GetTargetX() const
{
    return TargetX;
}

int Mage::GetTargetY() const
{
    return TargetY;
}

void Mage::SetTargetX(int value)
{
    if (value < 0)
        value = 0;

    TargetX = value;
}

void Mage::SetTargetY(int value)
{
    if (value < 0)
        value = 0;

    TargetY = value;
}

bool spellConfirmed = false;
bool spellCancelled = false;
bool targetingSpell = false;

// =========================
// AFFICHAGE TARGETING ZONE
// =========================

void Mage::displaySpellTargeting(Level& level, Player& player)
{
    int minX = player.GetPositionX() - SPELL_RADIUS;
    int maxX = player.GetPositionX() + SPELL_RADIUS;
    int minY = player.GetPositionY() - SPELL_RADIUS;
    int maxY = player.GetPositionY() + SPELL_RADIUS;

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            if (canDisplaySpellZone(level, player, x, y))
            {
                displaySpellZone(x, y);
            }
        }
    }

    displaySpellCursor();

    refresh();
}

// ==============
// SPELL CASTING
// ==============

bool Mage::castSpell(Level& level, Player& player)
{
    // Vérifier le mana
    if (!player.CanCastSpell() || player.GetMana() < SPELL_COST)
        return false;

    // Vérifier qu'un ennemi se trouve sur la case ciblée
    for (int i = 0; i < level.enemyCount; i++)
    {
        if (level.enemies[i].GetPositionX() == TargetX &&
            level.enemies[i].GetPositionY() == TargetY)
        {
            // Retirer le mana
            player.SetMana(player.GetMana() - SPELL_COST);

            // Les dégâts du sort correspondent aux dégâts du héros
            int spellDamage = player.GetDamage();

            level.enemies[i].SetLife(level.enemies[i].GetLife() - spellDamage);

            // Supprimer l'ennemi s'il est mort
            if (level.enemies[i].GetLife() <= 0)
            {
                for (int j = i; j < level.enemyCount - 1; j++)
                {
                    level.enemies[j] = level.enemies[j + 1];
                }

                level.enemyCount--;
            }

            return true;
        }
    }

    return false;
}