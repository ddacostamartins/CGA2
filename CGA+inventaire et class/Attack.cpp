#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Attack.h"
#include "Enemy.h"
#include "Player.h"







// =========================
// ATTAQUE DES ENNEMIS
// =========================
void enemyattack(Player& player, const Level& level)
{
    for (int i = 0; i < level.enemyCount; i++) {

        if (level.enemies[i].GetEnemyLife() <= 0)
            continue;

        if (player.GetPlayerX() == level.enemies[i].x &&
            player.GetPlayerY() == level.enemies[i].y) 
        {
            player.SetLife(player.GetLife() - level.enemies[i].GetEnemyDamage());

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

    if (enemy.GetEnemyLife() <= 0)
        return;

    int damage = player.GetTotalDamage();

    enemy.SetEnemyLife(enemy.GetEnemyLife() - damage);

    clear();

    attron(COLOR_PAIR(3));
    printw("===== ATTAQUE DU JOUEUR =====\n");
    printw("Tu attaques %s !\n", enemy.nom.c_str());
    printw("Tu infliges %d degats !\n", damage);
    attroff(COLOR_PAIR(3));

    if (enemy.GetEnemyLife() <= 0)
    {
        enemy.SetEnemyLife(0);

        attron(COLOR_PAIR(4));
        printw("L'ennemi est mort !\n");
        attroff(COLOR_PAIR(4));
    }

    printw("\nAppuie sur une touche...");
    refresh();
    getch();
}