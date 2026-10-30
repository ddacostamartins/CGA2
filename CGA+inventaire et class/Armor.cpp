#include <algorithm>
#include "Armor.h"

int Armors::GetDefense() const
{
    return Defense;
}

void Armors::SetDefense(int value)
{
    Defense = std::max(0, value);
}