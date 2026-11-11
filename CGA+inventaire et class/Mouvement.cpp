#include "Mouvement.h"
#include "Spell.h"
#include "Map.h"
#include <curses.h>
#include "Attack.h"
#include "Mage.h"
Mage mage;
bool handleEscape()
{
    if (mage.targetingSpell)
    {
        mage.targetingSpell = false;
        mage.spellCancelled = true;
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

    if (player.GetMana() < mage.SPELL_COST)
    {
        mvprintw(MAP_HEIGHT + 8, 2,
            "Mana insuffisant ! Il faut 20 mana.");
        refresh();
        return false;
    }

    mage.targetingSpell = true;
    mage.SetTargetX(player.GetPositionX());
    mage.SetTargetY(player.GetPositionY());

    return true;
}

bool moveSpellTarget(Player& player, int key)
{
    switch (key)
    {
    case 'z': case 'Z': mage.SetTargetY(mage.GetTargetY() -1); break;
    case 's': case 'S': mage.SetTargetY(mage.GetTargetY() + 1); break;
    case 'q': case 'Q': mage.SetTargetX(mage.GetTargetX() - 1); break;
    case 'd': case 'D': mage.SetTargetX(mage.GetTargetX() + 1); break;
    default:
        return false;
    }

    mage.SetTargetX( max(player.GetPositionX() - mage.SPELL_RADIUS,
        min(mage.GetTargetX(), player.GetPositionX() + mage.SPELL_RADIUS)));

    mage.SetTargetY( max(player.GetPositionY() - mage.SPELL_RADIUS,
        min(mage.GetTargetY(), player.GetPositionY() + mage.SPELL_RADIUS)));

    mage.SetTargetX( max(0, min(mage.GetTargetX(), MAP_WIDTH - 1)));
    mage.SetTargetY(max(0, min(mage.GetTargetY(), MAP_WIDTH - 1)));

    return true;
}

bool movePlayer(Player& player, Level& level, int key)
{
    int newX = player.GetPositionX();
    int newY = player.GetPositionY();

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
        if (level.enemies[i].GetLife() > 0 &&
            level.enemies[i].GetPositionX() == newX &&
            level.enemies[i].GetPositionY() == newY)
        {
            playerAttack(player, level, i);
            player.SetMana(player.GetMana() + 5);
            return true;
        }
    }

    player.SetPositionX(newX);
    player.SetPositionY(newY);
    player.SetMana(player.GetMana() + 5);

    return true;
}