#include <algorithm>
#include "Weapon.h"

int Weapon::GetDamage() const
{
    return Damage;
}

void Weapon::SetDamage(int value)
{
    Damage = std::max(0, value);
}

int Weapon::GetLifesteal() const
{
    return Lifesteal;
}

void Weapon::SetLifesteal(int value)
{
    Lifesteal = std::max(0, value);
}