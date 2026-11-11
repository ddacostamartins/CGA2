#include "Jeu.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <curses.h>

extern Mage mage;

void Jeu::lancerjeu()
{
    initialiserJeu();

    player = choisirClasse();

    currentLevel = 1;

    if (!initialiserNiveau(currentLevel, level, *player))
    {
        endwin();
        std::cout << "Erreur de chargement du niveau.\n";
        return;
    }

    displayMap(*player, level, currentLevel);

    jeuEnCours = true;

    while (jeuEnCours)
    {
     
        if (mage.targetingSpell)
        {
            gererCiblageSort(*player, level, currentLevel);

            Sleep(20);
            continue;
        }

     
        jeuEnCours = gererDeplacement(*player, level, currentLevel);

        Sleep(20);
    }

    endwin();
}