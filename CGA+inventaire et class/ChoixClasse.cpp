#include "ChoixClasse.h"
#include <memory>
#include "Player.h"
#include <curses.h>
#include "Mage.h"
#include "Warrior.h"
#include "WarriorMage.h"

std::unique_ptr<Player> choisirClasse()
{
    int choix;

    clear();
    printw("===== CHOISIS TA CLASSE =====\n\n");
    printw("1 - Mage\n");
    printw("2 - Guerrier\n");
    printw("3 - Guerrier-Mage\n\n");
    printw("Ton choix : ");
    refresh();

    choix = getch();

    switch (choix)
    {
    case '1':
        return std::make_unique<Mage>();

    case '2':
        return std::make_unique<Warrior>();

    case '3':
        return std::make_unique<WarriorMage>();

    default:
        printw("\nChoix invalide ! Appuie sur une touche.");
        refresh();
        getch();
        return choisirClasse();
    }
}