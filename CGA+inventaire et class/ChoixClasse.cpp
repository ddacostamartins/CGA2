#include "ChoixClasse.h"
#include <memory>
#include "Player.h"
#include <curses.h>
#include "Mage.h"
#include "Warrior.h"


std::unique_ptr<Player> choisirClasse()
{
    int choix;

    clear();
    printw("===== CHOISIS TA CLASSE =====\n\n");
    printw("1 - Mage\n");
    printw("2 - Warrior\n");
    printw("Ton choix : ");
    refresh();

    choix = getch();

    switch (choix)
    {
    case '1':
        return std::make_unique<Mage>();

    case '2':
        return std::make_unique<Warrior>();

    

    default:
        printw("\nChoix invalide ! Appuie sur une touche.");
        refresh();
        getch();
        return choisirClasse();
    }
}