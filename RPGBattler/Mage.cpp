#include "Mage.h"
#include <iostream>

Mage::Mage(const std::string& heroName)
	: Hero(heroName, 12, 12)
{

}
int Mage::Attack()
{
	int minDmg = 1;
	int generatedDmg = (rand() % maxDmg) + minDmg;
	std::cout << name << ", do you want to transform " << generatedDmg << "dmg to " << maxDmg - generatedDmg << "dmg? (y/n)";
	char special;
	std::cin >> special;
	if (special == 'y' || special == 'Y')
	{
		generatedDmg = maxDmg - generatedDmg; //change of formula to account for high level characters
	}
	return generatedDmg;
}