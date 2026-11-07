#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Mouvement.h"
#include "Map.h"
#include "Spell.h"
#include "Enemy.h"
#include "FonctionMouvement.h"

// ====================================
// VERIFICATION DES MOUVEMENT POSSIBLE
// ====================================

bool canMoveTo(const Level& level, int x, int y,
    int ignoredEnemy,
    bool isHero)
{
    if (!isInsideMap(x, y))
        return false;

    if (level.Map[y * MAP_WIDTH + x] == 1)
        return false;

    // Seuls les ennemis ne peuvent pas entrer dans la sortie
    if (!isHero &&
        x == level.sortie.x &&
        y == level.sortie.y)
        return false;

    for (int i = 0; i < level.enemyCount; i++)
    {
        if (i == ignoredEnemy)
            continue;

        if (level.enemies[i].x == x &&
            level.enemies[i].y == y)
            return false;
    }

    return true;
}

// =========================
// DEPLACEMENT DU HEROS
// =========================

bool movementhero(Player& player, Level& level)
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

// =========================
// DEPLACEMENT DES ENNEMIS
// =========================

void enemymovement(Level& level)
{
    for (int i = 0; i < level.enemyCount; i++)
    {
        if (level.enemies[i].Life <= 0)
            continue;

        int newX = level.enemies[i].x;
        int newY = level.enemies[i].y;

        // Choisir une direction aleatoire
        switch (rand() % 4)
        {
        case 0: newY--; break;
        case 1: newY++; break;
        case 2: newX--; break;
        case 3: newX++; break;
        }

        // Verifier si le deplacement est autorise
        if (!canMoveTo(level, newX, newY, i))
            continue;

        level.enemies[i].x = newX;
        level.enemies[i].y = newY;
    }
}