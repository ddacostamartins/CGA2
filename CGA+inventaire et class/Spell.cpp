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
    // La carte commence à la ligne 2 de l'écran
    const int MAP_START_ROW = 2;

    // La zone d'effet doit être centrée sur le heros
    int minX = player.GetPlayerX() - SPELL_RADIUS;
    int maxX = player.GetPlayerX() + SPELL_RADIUS;
    int minY = player.GetPlayerY() - SPELL_RADIUS;
    int maxY = player.GetPlayerY() + SPELL_RADIUS;

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            // Vérifier les limites de la carte
            if (!isInsideMap(x, y))
                continue;

            // Ne pas afficher la zone sur les murs
            if (level.Map[y * MAP_WIDTH + x] == 1)
                continue;

            // Ne pas afficher la zone sur la sortie
            if (x == level.sortie.x &&
                y == level.sortie.y)
                continue;

            // Préserver l'affichage des ennemis
            bool enemyFound = false;

            for (int i = 0; i < level.enemyCount; i++)
            {
                if (x == level.enemies[i].GetEnemyX() &&
                    y == level.enemies[i].GetEnemyY())
                {
                    enemyFound = true;
                    break;
                }
            }

            if (enemyFound)
                continue;

            // Préserver l'affichage du héros
            if (x == player.GetPlayerX() && y == player.GetPlayerY())
                continue;

            // Afficher la zone du sort
            attron(COLOR_PAIR(5));
            mvaddch(y + MAP_START_ROW, x * 2 + 2, '*');
            attroff(COLOR_PAIR(5));
        }
    }

    // Afficher le curseur de ciblage
    attron(COLOR_PAIR(2));
    mvaddch(targetY + MAP_START_ROW, targetX * 2 + 2, '+');
    attroff(COLOR_PAIR(2));

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
        if (level.enemies[i].GetEnemyX() == targetX &&
            level.enemies[i].GetEnemyY() == targetY)
        {
            // Retirer le mana
            player.SetMana(player.GetMana() - SPELL_COST);

            // Les dégâts du sort correspondent aux dégâts du héros
            int spellDamage = player.GetDamage();

            level.enemies[i].SetEnemyLife(level.enemies[i].GetEnemyLife() - spellDamage);

            // Supprimer l'ennemi s'il est mort
            if (level.enemies[i].GetEnemyLife() <= 0)
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