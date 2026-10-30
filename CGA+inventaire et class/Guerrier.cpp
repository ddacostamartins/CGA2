#include <iostream>
#include "Guerrier.h"

Guerrier::Guerrier() : Player(8, 5, 4)
{
}

void Guerrier::Displaystat() const
{
    std::cout << GetName() << " = Guerrier\n";
    std::cout << "Life : " << GetLife() << '\n';
    std::cout << "Damage : " << GetTotalDamage() << '\n';
    std::cout << "Armor : " << GetArmor() << '\n';
    std::cout << '\n';
}