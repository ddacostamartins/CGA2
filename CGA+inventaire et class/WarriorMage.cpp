#include <iostream>
#include "WarriorMage.h"

WarriorMage::WarriorMage() : Player(7, 6, 3, 5)
{
}

void WarriorMage::Displaystat() const
{
    std::cout << GetName() << " = Guerrier-Mage\n";
    std::cout << "Life : " << GetLife() << '\n';
    std::cout << "Damage : " << GetTotalDamage() << '\n';
    std::cout << "Armor : " << GetArmor() << '\n';
    std::cout << "Mana : " << GetMana() << '\n';
    std::cout << '\n';
}