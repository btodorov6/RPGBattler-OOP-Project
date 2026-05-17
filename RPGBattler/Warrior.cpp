#include "Warrior.h"
#include <print>
Warrior::Warrior(const std::string& heroName)
	: Hero(heroName, 20, 8)
{
	
}
int Warrior::Attack()
{
	int minDmg = 1;
	int generatedDmg = (rand() % maxDmg) + minDmg;
	return generatedDmg;
}

void Warrior::TakeDamage(int damage)
{
	int warriorBlock = (rand() % 4) + 1;
	damage -= warriorBlock;
	std::println("{} blocked {}dmg", name, warriorBlock);
	if (damage > 0)
	{
		currentHP -= damage;
		if (currentHP < 0)
		{
			currentHP = 0;
		}
	}
}