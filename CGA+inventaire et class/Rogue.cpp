#include <iostream>
#include "Rogue.h"

Rogue::Rogue() : Player(4, 7, 3)
{
}

void Rogue::Displaystat() const
{
    std::cout << GetName() << " = Rogue\n";
    std::cout << "Life : " << GetLife() << '\n';
    std::cout << "Damage : " << GetTotalDamage() << '\n';
    std::cout << "Armor : " << GetArmor() << '\n';
    std::cout << '\n';
}