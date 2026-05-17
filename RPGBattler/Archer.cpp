#include "Archer.h"
#include <iostream>
Archer::Archer(const std::string& heroName)
	:Hero(heroName, 15, 8)
{

}

int Archer::Attack()
{
	int minDmg = 1;
	int generatedDmg = (rand() % maxDmg) + minDmg;
	if (generatedDmg <= maxDmg/2) //adjusted formula for high level characters
	{
		std::cout << name << ", do you want to transform " << generatedDmg << "dmg to " << generatedDmg * 2 << "dmg? (y/n)";
		char special;
		std::cin >> special;
		if (special == 'y' || special == 'Y')
		{
			generatedDmg *= 2;
		}
	}
	return generatedDmg;
}