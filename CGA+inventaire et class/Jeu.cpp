#include "Jeu.h"
#include "FonctionJeu.h"
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <ctime>
#include <memory>
#include "ChoixClasse.h"
#include <curses.h>
#include "Map.h"
#include "Spell.h"


void lancerjeu()
{
    initialiserJeu();

    std::unique_ptr<Player> player = choisirClasse();

    Level level;
    int currentLevel = 1;

    if (!initialiserNiveau(currentLevel, level, *player))
    {
        endwin();
        std::cout << "Erreur de chargement du niveau.\n";
        return;
    }

    displayMap(*player, level, currentLevel);

    bool jeuEnCours = true;

    while (jeuEnCours)
    {
        // Mode de ciblage des sorts
        if (targetingSpell)
        {
            gererCiblageSort(*player, level, currentLevel);

            Sleep(20);
            continue;
        }

        // Déplacement du joueur
        jeuEnCours = gererDeplacement(*player, level, currentLevel);

        Sleep(20);
    }

    endwin();
}