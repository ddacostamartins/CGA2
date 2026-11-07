#include "FonctionMap.h"
#include "Map.h"
#include "Player.h"

#include <curses.h>

void displayLevelTitle(int currentLevel)
{
    attron(COLOR_PAIR(6));
    mvprintw(0, 2, "========== NIVEAU %d ==========", currentLevel);
    attroff(COLOR_PAIR(6));
}

void getTerrainAppearance(int cell, char& symbole, int& color)
{
    switch (cell)
    {
    case 0:
        symbole = '.';
        color = 8;
        break;

    case 1:
        symbole = '#';
        color = 4;
        break;

    case 2:
        symbole = '~';
        color = 7;
        break;

    default:
        symbole = '?';
        color = 8;
        break;
    }
}

void displayTerrain(int x, int y, Level& level)
{
    int cell = level.Map[y * MAP_WIDTH + x];

    char symbole;
    int color;

    getTerrainAppearance(cell, symbole, color);

    attron(COLOR_PAIR(color));
    mvaddch(y + 2, x * 2 + 2, symbole);
    attroff(COLOR_PAIR(color));
}

void displayHero(Player& player, int x, int y)
{
    if (x == player.GetPlayerX() &&
        y == player.GetPlayerY())
    {
        attron(COLOR_PAIR(3));
        mvaddch(y + 2, x * 2 + 2, 'H');
        attroff(COLOR_PAIR(3));
    }
}

void displayExit(Level& level, int x, int y)
{
    if (x == level.sortie.x &&
        y == level.sortie.y)
    {
        attron(COLOR_PAIR(6));
        mvaddch(y + 2, x * 2 + 2, 'E');
        attroff(COLOR_PAIR(6));
    }
}

void displayEnemies(Level& level, int x, int y)
{
    for (int i = 0; i < level.enemyCount; i++)
    {
        if (level.enemies[i].Life > 0 &&
            x == level.enemies[i].x &&
            y == level.enemies[i].y)
        {
            attron(COLOR_PAIR(2));
            mvaddch(y + 2, x * 2 + 2, 'X');
            attroff(COLOR_PAIR(2));
            break;
        }
    }
}