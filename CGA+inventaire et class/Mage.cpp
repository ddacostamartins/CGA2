#include <iostream>
#include "Mage.h"

Mage::Mage() : Player(3, 9, 2, 10)
{
}

void Mage::Displaystat() const
{
    std::cout << GetName() << " = Mage\n";
    std::cout << "Life : " << GetLife() << '\n';
    std::cout << "Damage : " << GetTotalDamage() << '\n';
    std::cout << "Armor : " << GetArmor() << '\n';
    std::cout << "Mana : " << GetMana() << '\n';
    std::cout << '\n';
}