#include <iostream>
#include "Tank.h"

Tank::Tank() : Player(10, 2, 5)
{
}

void Tank::Displaystat() const
{
    std::cout << GetName() << " = Tank\n";
    std::cout << "Life : " << GetLife() << '\n';
    std::cout << "Damage : " << GetTotalDamage() << '\n';
    std::cout << "Armor : " << GetArmor() << '\n';
    std::cout << '\n';
}