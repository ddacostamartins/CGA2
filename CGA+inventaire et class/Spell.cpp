#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Spell.h"
#include "Map.h"
#include "player.h"

bool spellConfirmed = false;
bool spellCancelled = false;
bool targetingSpell = false;

int targetX = 0;
int targetY = 0;

// =========================
// AFFICHAGE TARGETING ZONE
// =========================

void displaySpellTargeting(Level& level, Player& player)
{
    int minX = player.GetPlayerX() - SPELL_RADIUS;
    int maxX = player.GetPlayerX() + SPELL_RADIUS;
    int minY = player.GetPlayerY() - SPELL_RADIUS;
    int maxY = player.GetPlayerY() + SPELL_RADIUS;

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

bool castSpell(Level& level, Player& player)
{
    // Vérifier le mana
    if (!player.CanCastSpell() || player.GetMana() < SPELL_COST)
        return false;

    // Vérifier qu'un ennemi se trouve sur la case ciblée
    for (int i = 0; i < level.enemyCount; i++)
    {
        if (level.enemies[i].x == targetX &&
            level.enemies[i].y == targetY)
        {
            // Retirer le mana
            player.SetMana(player.GetMana() - SPELL_COST);

            // Les dégâts du sort correspondent aux dégâts du héros
            int spellDamage = player.GetDamage();

            level.enemies[i].Life -= spellDamage;

            // Supprimer l'ennemi s'il est mort
            if (level.enemies[i].Life <= 0)
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