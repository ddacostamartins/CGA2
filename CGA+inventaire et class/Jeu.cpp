#include "Jeu.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "Map.h"
#include "Spell.h"
#include "Level.h"
#include "Enemy.h"
#include "Mouvement.h"
#include "ChoixClasse.h"

void lancerjeu() 
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

    std::unique_ptr<Player> player = choisirClasse();
    Level level;
    int currentLevel = 1;

    if (!loadLevel(currentLevel, level))
    {
        endwin();
        std::cout << "Erreur de chargement du niveau.\n";
        return;
    }

    player->SetPlayerX(level.startX);
    player->SetPlayerY(level.startY);

    displayMap(*player, level, currentLevel);

    while (true)
    {
        // =========================
        // MODE DE CIBLAGE DU SORT
        // =========================
        if (targetingSpell)
        {
            movementhero(*player, level);

            displayMap(*player, level, currentLevel);

            if (targetingSpell)
            {
                displaySpellTargeting(level, *player);
            }
            else if (spellConfirmed)
            {
                bool spellSuccess = castSpell(level, *player);

                spellConfirmed = false;

                if (spellSuccess)
                {
                    // Tour des ennemis après le lancement du sort
                    enemymovement(level);
                    enemyattack(*player, level);
                }

                displayMap(*player, level, currentLevel);
            }
            else if (spellCancelled)
            {
                spellCancelled = false;
                displayMap(*player, level, currentLevel);
            }

            Sleep(20);
            continue;
        }

        // =========================
        // DEPLACEMENT DU HEROS
        // =========================
        if (movementhero(*player, level))
        {
            // Entrée en mode ciblage
            if (targetingSpell)
            {
                displayMap(*player, level, currentLevel);
                displaySpellTargeting(level, *player);
                continue;
            }

            // Annulation du sort
            if (spellCancelled)
            {
                spellCancelled = false;
                displayMap(*player, level, currentLevel);
                continue;
            }

            // Vérifier la sortie
            if (player->GetPlayerX() == level.sortie.x &&
                player->GetPlayerY() == level.sortie.y)
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

                player->SetPlayerX(level.startX);
                player->SetPlayerY(level.startY);

                displayMap(*player, level, currentLevel);
                continue;
            }

            // Tour des ennemis après un déplacement valide
            enemymovement(level);
            enemyattack(*player, level);

            displayMap(*player, level, currentLevel);
        }

        Sleep(20);
    }

    endwin();
    return;
}