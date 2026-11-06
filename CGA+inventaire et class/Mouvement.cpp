#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Mouvement.h"
#include "Map.h"
#include "Spell.h"
#include "Enemy.h"
#include "Attack.h"

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

        if (level.enemies[i].GetEnemyX() == x &&
            level.enemies[i].GetEnemyY() == y)
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
        // Vérifier la classe
        if (!player.CanCastSpell())
        {
            mvprintw(MAP_HEIGHT + 8, 2,
                "Cette classe ne peut pas utiliser de sort !");
            refresh();
            return false;
        }

        // Vérifier le mana
        if (player.GetMana() < SPELL_COST)
        {
            mvprintw(MAP_HEIGHT + 8, 2,
                "Mana insuffisant ! Il faut 20 mana.");
            refresh();
            return false;
        }

        // Activer le ciblage
        targetingSpell = true;
        targetX = player.GetPlayerX();
        targetY = player.GetPlayerY();

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

        if (targetX < player.GetPlayerX() - SPELL_RADIUS) targetX = player.GetPlayerX() - SPELL_RADIUS;
        if (targetX > player.GetPlayerX() + SPELL_RADIUS) targetX = player.GetPlayerX() + SPELL_RADIUS;
        if (targetY < player.GetPlayerY() - SPELL_RADIUS) targetY = player.GetPlayerY() - SPELL_RADIUS;
        if (targetY > player.GetPlayerY() + SPELL_RADIUS) targetY = player.GetPlayerY() + SPELL_RADIUS;

        if (targetX < 0) targetX = 0;
        if (targetX >= MAP_WIDTH) targetX = MAP_WIDTH - 1;
        if (targetY < 0) targetY = 0;
        if (targetY >= MAP_HEIGHT) targetY = MAP_HEIGHT - 1;

        return true;
    }

    int newX = player.GetPlayerX();
    int newY = player.GetPlayerY();

    switch (key)
    {
    case 'z': case 'Z': newY--; break;
    case 's': case 'S': newY++; break;
    case 'q': case 'Q': newX--; break;
    case 'd': case 'D': newX++; break;
    default:
        return false;
    }

    // Vérifier les limites et les murs
    if (!isInsideMap(newX, newY))
        return false;

    if (level.Map[newY * MAP_WIDTH + newX] == 1)
        return false;

    // Vérifier si une case contient un ennemi
    for (int i = 0; i < level.enemyCount; i++)
    {
        if (level.enemies[i].GetEnemyLife() > 0 &&
            level.enemies[i].GetEnemyX() == newX &&
            level.enemies[i].GetEnemyY() == newY)
        {
            playerAttack(player, level, i);
            player.SetMana(player.GetMana() + 5);
            return true;
        }
    }

    // Déplacement normal
    player.SetPlayerX(newX);
    player.SetPlayerY(newY);

    // Regeneration de 5 mana après un déplacement valide
    player.SetMana(player.GetMana() + 5);

    return true;
}

// =========================
// DEPLACEMENT DES ENNEMIS
// =========================

void enemymovement(Level& level)
{
    for (int i = 0; i < level.enemyCount; i++)
    {
        if (level.enemies[i].GetEnemyLife() <= 0)
            continue;

        int newX = level.enemies[i].GetEnemyX();
        int newY = level.enemies[i].GetEnemyY();

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

        level.enemies[i].SetEnemyX(newX);
        level.enemies[i].SetEnemyY(newY);
    }
}