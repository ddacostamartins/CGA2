#include <iostream>
#include "WarriorMage.h"
#include "Player.h"
#include "Warrior.h"
#include "Mage.h"


WarriorMage::WarriorMage() : Player(6,6,6,15)
{
}

void WarriorMage::Displaystat() const
{
    std::cout << GetName() << " = WarriorMage\n";
    std::cout << "Life : " << GetLife() << '\n';
    std::cout << "Damage : " << GetTotalDamage() << '\n';
    std::cout << "Armor : " << GetArmor() << '\n';
    std::cout << "Mana : " << GetMana() << '\n';
    std::cout << '\n';
}