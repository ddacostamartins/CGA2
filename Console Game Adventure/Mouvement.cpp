#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Mouvement.h"
#include "Map.h"
#include "Spell.h"

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

bool movementhero(Hero& hero, const Level& level)
{
    int key = getch();

    if (key == ERR)
        return false;

    if (key == 27)
    {
        if (targetingSpell)
        {
            targetingSpell = false;
            spellCancelled = true;
            return true;
        }

        endwin();
        exit(0);
    }

    if (key == 'e' || key == 'E')
    {
        targetingSpell = true;
        targetX = hero.x;
        targetY = hero.y;
        return true;
    }

    if (targetingSpell)
    {

        if (key == '\n' || key == '\r' || key == KEY_ENTER)
        {
            spellConfirmed = true;
            targetingSpell = false;
            return true;
        }

        switch (key)
        {
        case 'z': case 'Z': targetY--; break;
        case 's': case 'S': targetY++; break;
        case 'q': case 'Q': targetX--; break;
        case 'd': case 'D': targetX++; break;
        default:
            return false;
        }

        // Limiter le curseur à la portée du sort
        if (targetX < hero.x - SPELL_RADIUS) targetX = hero.x - SPELL_RADIUS;
        if (targetX > hero.x + SPELL_RADIUS) targetX = hero.x + SPELL_RADIUS;
        if (targetY < hero.y - SPELL_RADIUS) targetY = hero.y - SPELL_RADIUS;
        if (targetY > hero.y + SPELL_RADIUS) targetY = hero.y + SPELL_RADIUS;

        // Empêcher le curseur de sortir de la carte
        if (targetX < 0) targetX = 0;
        if (targetX >= MAP_WIDTH) targetX = MAP_WIDTH - 1;
        if (targetY < 0) targetY = 0;
        if (targetY >= MAP_HEIGHT) targetY = MAP_HEIGHT - 1;

        return true;
    }

    int newX = hero.x;
    int newY = hero.y;

    switch (key)
    {
    case 'z': case 'Z': newY--; break;
    case 's': case 'S': newY++; break;
    case 'q': case 'Q': newX--; break;
    case 'd': case 'D': newX++; break;
    default:
        return false;
    }

    // Le heros ne peut pas entrer dans un mur,
    // sortir de la carte ou toucher un ennemi.
    if (!canMoveTo(level, newX, newY, -1, true))
        return false;

    hero.x = newX;
    hero.y = newY;

    return true;
}

// =========================
// DEPLACEMENT DES ENNEMIS
// =========================

void enemymovement(Level& level)
{
    for (int i = 0; i < level.enemyCount; i++)
    {
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