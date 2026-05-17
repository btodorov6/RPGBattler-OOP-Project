#include "Mage.h"
#include <iostream>
#include <print>

Mage::Mage(const std::string& heroName)
	: Hero(heroName, 12, 12)
{

}
int Mage::Attack()
{
	int minDmg = 1;
	int generatedDmg = (rand() % maxDmg) + minDmg;
	std::print("{}, do you want to transform {}dmg to {}dmg? (y/n) ", name, generatedDmg, maxDmg - generatedDmg);
	char special;
	std::cin >> special;
	if (special == 'y' || special == 'Y')
	{
		generatedDmg = maxDmg - generatedDmg; //change of formula to account for high level characters
	}
	return generatedDmg;
}