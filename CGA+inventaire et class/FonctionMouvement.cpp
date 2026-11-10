#include "FonctionMouvement.h"
#include "Spell.h"
#include "Map.h"
#include <curses.h>
#include "Attack.h"

bool handleEscape()
{
    if (targetingSpell)
    {
        targetingSpell = false;
        spellCancelled = true;
        return true;
    }

    endwin();
    exit(0);
}

bool startSpellTargeting(Player& player)
{
    if (!player.CanCastSpell())
    {
        mvprintw(MAP_HEIGHT + 8, 2,
            "Cette classe ne peut pas utiliser de sort !");
        refresh();
        return false;
    }

    if (player.GetMana() < SPELL_COST)
    {
        mvprintw(MAP_HEIGHT + 8, 2,
            "Mana insuffisant ! Il faut 20 mana.");
        refresh();
        return false;
    }

    targetingSpell = true;
    targetX = player.GetPlayerX();
    targetY = player.GetPlayerY();

    return true;
}

bool moveSpellTarget(Player& player, int key)
{
    switch (key)
    {
    case 'z': case 'Z': targetY--; break;
    case 's': case 'S': targetY++; break;
    case 'q': case 'Q': targetX--; break;
    case 'd': case 'D': targetX++; break;
    default:
        return false;
    }

    targetX = max(player.GetPlayerX() - SPELL_RADIUS,
        min(targetX, player.GetPlayerX() + SPELL_RADIUS));

    targetY = max(player.GetPlayerY() - SPELL_RADIUS,
        min(targetY, player.GetPlayerY() + SPELL_RADIUS));

    targetX = max(0, min(targetX, MAP_WIDTH - 1));
    targetY = max(0, min(targetY, MAP_HEIGHT - 1));

    return true;
}

bool movePlayer(Player& player, Level& level, int key)
{
    int newX = player.GetPlayerX();
    int newY = player.GetPlayerY();

    switch (key)
    {
    case 'z': case 'Z': newY--; break;
    case 's': case 'S': newY++; break;
    case 'q': case 'Q': newX--; break;
    case 'd': case 'D': newX++; break;
    default:
        return false;
    }

    if (!isInsideMap(newX, newY))
        return false;

    if (level.Map[newY * MAP_WIDTH + newX] == 1)
        return false;

    for (int i = 0; i < level.enemyCount; i++)
    {
        if (level.enemies[i].Life > 0 &&
            level.enemies[i].x == newX &&
            level.enemies[i].y == newY)
        {
            playerAttack(player, level, i);
            player.SetMana(player.GetMana() + 5);
            return true;
        }
    }

    player.SetPlayerX(newX);
    player.SetPlayerY(newY);
    player.SetMana(player.GetMana() + 5);

    return true;
}

