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

	if (isBladeActive)
	{
		generatedDmg *= 2;
		isBladeActive = false;
	}

	return generatedDmg;
}

void Warrior::TakeDamage(int damage)
{
	if (isShieldActive)
	{
		isAffectedByMirror = false;
		isShieldActive = false;
		return;
	}
	if (!isAffectedByMirror)
	{
		int warriorBlock = (rand() % (maxHP / 5)) + 1; //change of formula to account for high level characters
		damage -= warriorBlock;
		std::println("{} blocked {}dmg", name, warriorBlock);
	}
	else
	{
		std::println("Mirror stops {} from using his special...", name);
		isAffectedByMirror = false;
	}
	if (damage > 0)
	{
		currentHP -= damage;
		if (currentHP < 0)
		{
			currentHP = 0;
		}
	}
}