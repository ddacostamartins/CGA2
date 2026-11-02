#include <iostream>
#include <curses.h>
#include <ctime>
#include <cstdlib>
#include <windows.h>

#include "Player.h"
#include "Warrior.h"
#include "Mage.h"
#include "WarriorMage.h"

int main()
{
	Warrior player1;
	Mage player2;
	WarriorMage player3;

	player1.Displaystat();
	player2.Displaystat();
	player3.Displaystat();
}