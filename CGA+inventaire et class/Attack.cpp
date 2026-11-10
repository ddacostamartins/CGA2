#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Attack.h"
#include "Player.h"
#include "Enemy.h"

// =========================
// ATTAQUE DES ENNEMIS
// =========================
void enemyattack(Player& player, const Level& level)
{
    for (int i = 0; i < level.enemyCount; i++) {

        if (level.enemies[i].GetLife() <= 0)
            continue;

        if (player.GetPositionX() == level.enemies[i].GetPositionX() &&
            player.GetPositionY() == level.enemies[i].GetPositionY())
        {
            player.SetLife(player.GetLife() - level.enemies[i].GetDamage());

            if (player.GetLife() <= 0) {
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

// =========================
// ATTAQUE DU JOUEUR
// =========================

void playerAttack(Player& player, Level& level, int enemyIndex)
{
    if (enemyIndex < 0 || enemyIndex >= level.enemyCount)
        return;

    Enemy& enemy = level.enemies[enemyIndex];

    if (enemy.GetLife() <= 0)
        return;

    int damage = player.GetTotalDamage();

    enemy.SetLife(enemy.GetLife() - damage);

    clear();

    attron(COLOR_PAIR(3));
    printw("===== ATTAQUE DU JOUEUR =====\n");
    printw("Tu attaques %s !\n", enemy.GetName().c_str());
    printw("Tu infliges %d degats !\n", damage);
    attroff(COLOR_PAIR(3));

    if (enemy.GetLife() <= 0)
    {
        enemy.SetLife(0);

        attron(COLOR_PAIR(4));
        printw("L'ennemi est mort !\n");
        attroff(COLOR_PAIR(4));
    }

    printw("\nAppuie sur une touche...");
    refresh();
    getch();
}