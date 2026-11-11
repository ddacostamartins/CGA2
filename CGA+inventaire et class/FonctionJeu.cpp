#include "Jeu.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <memory>

#include "Map.h"
#include "Mage.h"
#include "Level.h"
#include "Attack.h"
#include "Mouvement.h"
#include "ChoixClasse.h"
#include "Enemy.h"

Mage mage;
Enemy enemy;

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

    player.SetPositionX(level.startX);
    player.SetPositionY(level.startY);

    return true;
}

void tourEnnemis(Player& player, Level& level)
{
    enemy.enemymovement(level);
    enemyattack(player, level);
}

void gererCiblageSort(Player& player, Level& level, int currentLevel)
{
    player.movementhero(player, level);
    displayMap(player, level, currentLevel);

    if (mage.targetingSpell)
    {
        mage.displaySpellTargeting(level, player);
    }
    else if (mage.spellConfirmed)
    {
        bool spellSuccess = mage.castSpell(level, player);
        mage.spellConfirmed = false;

        if (spellSuccess)
        {
            tourEnnemis(player, level);
        }

        displayMap(player, level, currentLevel);
    }
    else if (mage.spellCancelled)
    {
        mage.spellCancelled = false;
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
    if (!player.movementhero(player, level))
    {
        return true;
    }

    if (mage.targetingSpell)
    {
        displayMap(player, level, currentLevel);
        mage.displaySpellTargeting(level, player);
        return true;
    }

    if (mage.spellCancelled)
    {
        mage.spellCancelled = false;
        displayMap(player, level, currentLevel);
        return true;
    }

    // Vérification de la sortie
    if (player.GetPositionX() == level.sortie.x &&
        player.GetPositionY() == level.sortie.y)
    {
        return changerNiveau(currentLevel, level, player);
    }

    tourEnnemis(player, level);
    displayMap(player, level, currentLevel);

    return true;
}