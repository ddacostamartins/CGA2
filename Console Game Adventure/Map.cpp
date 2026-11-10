#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Map.h"

// =========================
// VERIFICATION DES LIMITES
// =========================
bool isInsideMap(int x, int y)
{
    return x >= 0 && x < MAP_WIDTH &&
        y >= 0 && y < MAP_HEIGHT;
}

// =========================
// AFFICHAGE DE LA CARTE
// =========================
void displayMap(const Hero& hero, const Level& level, int currentLevel) {

    clear();
    refresh();

    printw("===== NIVEAU %d", currentLevel);
    printw(" =====\n\n");

    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_WIDTH; x++) {

            if (x == hero.x && y == hero.y) {
                attron(COLOR_PAIR(3));
                printw("H");
                attroff(COLOR_PAIR(3));
            }
            else if (x == level.sortie.x &&
                y == level.sortie.y) {
                attron(COLOR_PAIR(6));
                printw("E");
                attroff(COLOR_PAIR(6));
            }
            else {
                bool enemyFound = false;

                for (int i = 0; i < level.enemyCount; i++) {
                    if (x == level.enemies[i].x &&
                        y == level.enemies[i].y) {
                        attron(COLOR_PAIR(2));
                        printw("X");
                        attroff(COLOR_PAIR(2));
                        enemyFound = true;
                        break;
                    }
                }

                if (!enemyFound) {
                    int cell = level.Map[y * MAP_WIDTH + x];

                    if (cell == 0) {
                        attron(COLOR_PAIR(8));
                        printw(".");
                        attroff(COLOR_PAIR(8));
                    }
                    else if (cell == 1) {
                        attron(COLOR_PAIR(4));
                        printw("A");
                        attroff(COLOR_PAIR(4));
                    }
                    else if (cell == 2) {
                        attron(COLOR_PAIR(7));
                        printw("~");
                        attroff(COLOR_PAIR(7));
                    }
                }
            }
        }

        printw("\n");
    }

    printw("\n");
    attron(COLOR_PAIR(3));
    printw("Vie du hero : %d", hero.Life);
    attroff(COLOR_PAIR(3));
    printw("\n");
    attron(COLOR_PAIR(3));
    printw("H = Hero");
    attroff(COLOR_PAIR(3));
    attron(COLOR_PAIR(2));
    printw(" | X = Ennemi");
    attroff(COLOR_PAIR(2));
    attron(COLOR_PAIR(6));
    printw(" | E = Sortie\n");
    attroff(COLOR_PAIR(6));
    attron(COLOR_PAIR(4));
    printw("A = Mur");
    attroff(COLOR_PAIR(4));
    attron(COLOR_PAIR(7));
    printw(" | ~ = Eau\n");
    attroff(COLOR_PAIR(7));
    attron(COLOR_PAIR(8));
    printw("ZQSD pour bouger | Echap pour quitter\n");
    attroff(COLOR_PAIR(8));
    refresh();
}