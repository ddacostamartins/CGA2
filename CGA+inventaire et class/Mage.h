#pragma once

#include "Player.h"
#include "Level.h"
#include "Spell.h"

class Mage : public Player
{
protected:
    int TargetX = 0;
    int TargetY = 0;

public:
    Mage(int life, int damage, int armorValue, int mana, int playerX, int playerY, int maxLife, int maxmana, int targetX = 0, int targetY = 0);

    const char* GetName() 
    {
        return "Mage";
    }

    bool CanCastSpell() const override
    {
        return true;
    }

    bool spellConfirmed;
    bool spellCancelled;
    bool targetingSpell;

    const int SPELL_RADIUS = 3;
    const int SPELL_DAMAGE = 1;
    const int SPELL_COST = 20;

    void displaySpellTargeting(Level& level, Player& player);
    bool castSpell(Level& level, Player& player);

    int GetTargetX() const;
    int GetTargetY() const;

    void SetTargetX(int value);
    void SetTargetY(int value);
};