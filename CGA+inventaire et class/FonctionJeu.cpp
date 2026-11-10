#include "Jeu.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "Map.h"
#include "Spell.h"
#include "Level.h"
#include "Attack.h"
#include "Mouvement.h"
#include "ChoixClasse.h"

void initialiserJeu()
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
}

bool initialiserNiveau(int currentLevel, Level& level, Player& player)
{
    if (!loadLevel(currentLevel, level))
    {
        endwin();
        std::cout << "Erreur de chargement du niveau.\n";
        return false;
    }

    player.SetPlayerX(level.startX);
    player.SetPlayerY(level.startY);

    return true;
}

void tourEnnemis(Player& player, Level& level)
{
    enemymovement(level);
    enemyattack(player, level);
}

void gererCiblageSort(Player& player, Level& level, int currentLevel)
{
    movementhero(player, level);
    displayMap(player, level, currentLevel);

    if (targetingSpell)
    {
        displaySpellTargeting(level, player);
    }
    else if (spellConfirmed)
    {
        bool spellSuccess = castSpell(level, player);
        spellConfirmed = false;

        if (spellSuccess)
        {
            tourEnnemis(player, level);
        }

        displayMap(player, level, currentLevel);
    }
    else if (spellCancelled)
    {
        spellCancelled = false;
        displayMap(player, level, currentLevel);
    }
}

bool changerNiveau(int& currentLevel, Level& level, Player& player)
{
    clear();

    attron(COLOR_PAIR(4));
    printw("===== NIVEAU TERMINE =====\n");
    printw("Tu as termine le niveau %d !\n", currentLevel);
    printw("Appuie sur une touche...");
    attroff(COLOR_PAIR(4));

    refresh();
    getch();

    currentLevel++;

    if (!initialiserNiveau(currentLevel, level, player))
    {
        clear();

        attron(COLOR_PAIR(4));
        printw("===== FIN DU JEU =====\n");
        printw("Bravo ! Tu as termine tous les niveaux.\n");
        printw("Appuie sur une touche pour quitter...");
        attroff(COLOR_PAIR(4));

        refresh();
        getch();

        return false;
    }

    return true;
}

bool gererDeplacement(Player& player, Level& level, int& currentLevel)
{
    if (!movementhero(player, level))
    {
        return true;
    }

    if (targetingSpell)
    {
        displayMap(player, level, currentLevel);
        displaySpellTargeting(level, player);
        return true;
    }

    if (spellCancelled)
    {
        spellCancelled = false;
        displayMap(player, level, currentLevel);
        return true;
    }

    // Vérification de la sortie
    if (player.GetPlayerX() == level.sortie.x &&
        player.GetPlayerY() == level.sortie.y)
    {
        return changerNiveau(currentLevel, level, player);
    }

    tourEnnemis(player, level);
    displayMap(player, level, currentLevel);

    return true;
}