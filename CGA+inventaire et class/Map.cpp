#include "Map.h"
#include "Player.h"
#include "FonctionMap.h"

#include <curses.h>



// =========================
// VERIFICATION DES LIMITES
// =========================
bool isInsideMap(int x, int y)
{
    return x >= 0 && x < MAP_WIDTH &&
        y >= 0 && y < MAP_HEIGHT;
}

// =========================
// AFFICHAGE DE LA CARTE
// =========================
void displayMap(Player& player, Level& level, int currentLevel)
{
    clear();

    displayLevelTitle(currentLevel);

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            displayTerrain(x, y, level);

            if (x == player.GetPlayerX() &&
                y == player.GetPlayerY())
            {
                displayHero(player, x, y);
            }
            else if (x == level.sortie.x &&
                y == level.sortie.y)
            {
                displayExit(level, x, y);
            }
            else
            {
                displayEnemies(level, x, y);
            }
        }
    }

    refresh();
}

    // =========================
    // STATISTIQUES DU PERSONNAGE
    // =========================

    int infoX = MAP_WIDTH * 2 + 7;
    int infoY = 2;

    attron(COLOR_PAIR(6));
    mvprintw(infoY, infoX, "===== PERSONNAGE =====");
    attroff(COLOR_PAIR(6));

    mvprintw(infoY + 2, infoX, "Classe : %s",
        player.GetClassName());

    attron(COLOR_PAIR(3));
    mvprintw(infoY + 4, infoX, "Vie : %d",
        player.GetLife());
    attroff(COLOR_PAIR(3));

    mvprintw(infoY + 5, infoX, "Degats : %d",
        player.GetTotalDamage());

    mvprintw(infoY + 6, infoX, "Armure : %d",
        player.GetArmor());

    attron(COLOR_PAIR(5));
    mvprintw(infoY + 7, infoX, "Mana : %d",
        player.GetMana());
    attroff(COLOR_PAIR(5));

    // =========================
    // LEGENDE
    // =========================

    int legendY = MAP_HEIGHT + 4;

    attron(COLOR_PAIR(3));
    mvprintw(legendY, 2, "H");
    attroff(COLOR_PAIR(3));
    printw(" = Hero   ");

    attron(COLOR_PAIR(2));
    printw("X");
    attroff(COLOR_PAIR(2));
    printw(" = Ennemi   ");

    attron(COLOR_PAIR(6));
    printw("E");
    attroff(COLOR_PAIR(6));
    printw(" = Sortie\n");

    attron(COLOR_PAIR(4));
    mvprintw(legendY + 1, 2, "#");
    attroff(COLOR_PAIR(4));
    printw(" = Mur   ");

    attron(COLOR_PAIR(7));
    printw("~");
    attroff(COLOR_PAIR(7));
    printw(" = Eau   ");

    attron(COLOR_PAIR(8));
    printw(".");
    attroff(COLOR_PAIR(8));
    printw(" = Sol\n");

    mvprintw(legendY + 3, 2,
        "ZQSD : Deplacement | Echap : Quitter");

    refresh();
}