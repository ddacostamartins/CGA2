#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Spell.h"
#include "Map.h"

bool spellConfirmed = false;
bool spellCancelled = false;
bool targetingSpell = false;

int targetX = 0;
int targetY = 0;

// =========================
// AFFICHAGE TARGETING ZONE
// =========================

void displaySpellTargeting(Level& level, Hero& hero)
{
    // La carte commence à la ligne 2 de l'écran
    const int MAP_START_ROW = 2;

    // La zone d'effet doit être centrée sur le heros
    int minX = hero.x - SPELL_RADIUS;
    int maxX = hero.x + SPELL_RADIUS;
    int minY = hero.y - SPELL_RADIUS;
    int maxY = hero.y + SPELL_RADIUS;

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
                if (x == level.enemies[i].x &&
                    y == level.enemies[i].y)
                {
                    enemyFound = true;
                    break;
                }
            }

            if (enemyFound)
                continue;

            // Préserver l'affichage du héros
            if (x == hero.x && y == hero.y)
                continue;

            // Afficher la zone du sort
            attron(COLOR_PAIR(5));
            mvaddch(y + MAP_START_ROW, x, '*');
            attroff(COLOR_PAIR(5));
        }
    }

    // Afficher le curseur de ciblage
    attron(COLOR_PAIR(2));
    mvaddch(targetY + MAP_START_ROW, targetX, '+');
    attroff(COLOR_PAIR(2));

    refresh();
}

// ==============
// SPELL CASTING
// ==============

void castSpell(Level& level)
{
    for (int i = 0; i < level.enemyCount; i++)
    {
        // Toucher uniquement l'ennemi sur la case ciblée
        if (level.enemies[i].x == targetX &&
            level.enemies[i].y == targetY)
        {
            level.enemies[i].Life -= SPELL_DAMAGE;

            // Supprimer l'ennemi s'il n'a plus de vie
            if (level.enemies[i].Life <= 0)
            {
                for (int j = i; j < level.enemyCount - 1; j++)
                {
                    level.enemies[j] = level.enemies[j + 1];
                }

                level.enemyCount--;
                i--;
            }
        }
    }
}