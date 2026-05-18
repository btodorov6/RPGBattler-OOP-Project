#include "Archer.h"
#include <iostream>
#include <print>
Archer::Archer(const std::string& heroName)
	:Hero(heroName, 15, 8)
{

}

int Archer::Attack()
{
	int minDmg = 1;
	int generatedDmg = (rand() % maxDmg) + minDmg;
	
	if (!isAffectedByMirror)
	{
		if (generatedDmg <= maxDmg / 2) //adjusted formula for high level characters
		{
			std::print("{}, do you want to transform {}dmg to {}dmg? (y/n) ", name, generatedDmg, generatedDmg * 2);
			char special;
			std::cin >> special;
			if (special == 'y' || special == 'Y')
			{
				generatedDmg *= 2;
			}
		}
	}
	else
	{
		std::println("Mirror stops {} from using his special...", name);
		isAffectedByMirror = false;
	}

	if (isBladeActive)
	{
		generatedDmg *= 2;
		isBladeActive = false;
	}

	return generatedDmg;
}