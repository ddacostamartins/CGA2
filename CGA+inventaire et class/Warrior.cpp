#include <iostream>
#include "Warrior.h"

Warrior::Warrior() : Player(10, 4, 5,0)
{
}

void Warrior::Displaystat() const
{
    std::cout << GetName() << " = Warrior\n";
    std::cout << "Life : " << GetLife() << '\n';
    std::cout << "Damage : " << GetTotalDamage() << '\n';
    std::cout << "Armor : " << GetArmor() << '\n';
    std::cout << '\n';
}