#include "FonctionSpell.h"
#include "Level.h"
#include "Player.h"
#include "Spell.h"
#include "Map.h"

#include <curses.h>

bool isEnemyAt(Level& level, int x, int y)
{
    for (int i = 0; i < level.enemyCount; i++)
    {
        if (level.enemies[i].x == x &&
            level.enemies[i].y == y)
            return true;
    }

    return false;
}

bool canDisplaySpellZone(Level& level, Player& player, int x, int y)
{
    if (!isInsideMap(x, y))
        return false;

    if (level.Map[y * MAP_WIDTH + x] == 1)
        return false;

    if (x == level.sortie.x && y == level.sortie.y)
        return false;

    if (isEnemyAt(level, x, y))
        return false;

    if (x == player.GetPlayerX() &&
        y == player.GetPlayerY())
        return false;

    return true;
}

void displaySpellZone(int x, int y)
{
    const int MAP_START_ROW = 2;

    attron(COLOR_PAIR(5));
    mvaddch(y + MAP_START_ROW, x * 2 + 2, '*');
    attroff(COLOR_PAIR(5));
}

void displaySpellCursor()
{
    const int MAP_START_ROW = 2;

    attron(COLOR_PAIR(2));
    mvaddch(targetY + MAP_START_ROW, targetX * 2 + 2, '+');
    attroff(COLOR_PAIR(2));
}