#include <iostream>
#include <conio.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

#include "Map.h"
#include "Spell.h"
#include "Levels.h"
#include "Enemy.h"
#include "Mouvement.h"

// =========================
// PROGRAMME PRINCIPAL
// =========================

int main()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_BLACK, COLOR_WHITE);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_GREEN, COLOR_BLACK);
        init_pair(4, COLOR_YELLOW, COLOR_BLACK);
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(7, COLOR_CYAN, COLOR_BLACK);
        init_pair(8, COLOR_WHITE, COLOR_BLACK);
    }

    srand(static_cast<unsigned int>(time(nullptr)));

    Hero hero;
    Level level;
    int currentLevel = 1;

    if (!loadLevel(currentLevel, level))
    {
        endwin();
        std::cout << "Erreur de chargement du niveau.\n";
        return 1;
    }

    hero.x = level.startX;
    hero.y = level.startY;

    displayMap(hero, level, currentLevel);

    while (true)
    {
        // =========================
        // MODE DE CIBLAGE DU SORT
        // =========================
        if (targetingSpell)
        {
            movementhero(hero, level);

            displayMap(hero, level, currentLevel);

            if (targetingSpell)
            {
                displaySpellTargeting(level, hero);
            }
            else if (spellConfirmed)
            {
                castSpell(level);
                spellConfirmed = false;

                enemymovement(level);
                enemyattack(hero, level);

                displayMap(hero, level, currentLevel);
            }
            else if (spellCancelled)
            {
                spellCancelled = false;
                displayMap(hero, level, currentLevel);
            }

            Sleep(20);
            continue;
        }

        // =========================
        // DEPLACEMENT DU HEROS
        // =========================
        if (movementhero(hero, level))
        {
            // Entrée en mode ciblage
            if (targetingSpell)
            {
                displayMap(hero, level, currentLevel);
                displaySpellTargeting(level, hero);
                continue;
            }

            // Annulation du sort
            if (spellCancelled)
            {
                spellCancelled = false;
                displayMap(hero, level, currentLevel);
                continue;
            }

            // Vérifier la sortie
            if (hero.x == level.sortie.x &&
                hero.y == level.sortie.y)
            {
                clear();

                attron(COLOR_PAIR(4));
                printw("===== NIVEAU TERMINE =====\n");
                printw("Tu as termine le niveau %d !\n",
                    currentLevel);
                printw("Appuie sur une touche...");
                attroff(COLOR_PAIR(4));

                refresh();
                getch();

                currentLevel++;

                if (!loadLevel(currentLevel, level))
                {
                    clear();

                    attron(COLOR_PAIR(4));
                    printw("===== FIN DU JEU =====\n");
                    printw("Bravo ! Tu as termine tous les niveaux.\n");
                    printw("Appuie sur une touche pour quitter...");
                    attroff(COLOR_PAIR(4));

                    refresh();
                    getch();
                    break;
                }

                hero.x = level.startX;
                hero.y = level.startY;

                displayMap(hero, level, currentLevel);
                continue;
            }

            // Tour des ennemis après un déplacement valide
            enemymovement(level);
            enemyattack(hero, level);

            displayMap(hero, level, currentLevel);
        }

        Sleep(20);
    }

    endwin();
    return 0;
}