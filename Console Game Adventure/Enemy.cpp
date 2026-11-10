#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Enemy.h"

// =========================
// ATTAQUE DES ENNEMIS
// =========================
void enemyattack(Hero& hero, const Level& level) {

    for (int i = 0; i < level.enemyCount; i++) {

        if (hero.x == level.enemies[i].x &&
            hero.y == level.enemies[i].y) {

            hero.Life -= level.enemies[i].damage;

            if (hero.Life <= 0) {
                clear();
                refresh();
                attron(COLOR_PAIR(2));
                printw("===== GAME OVER =====\n");
                printw("Appuie sur une touche...");
                attroff(COLOR_PAIR(2));
                getch();
                exit(0);
            }

            // Un seul degat par tour
            break;
        }
    }
}