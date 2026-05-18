#include "HealingPotion.h"
#include <print>
std::string HealingPotion::getName()
{
	return "Healing Potion";
}

void HealingPotion::use(Hero& target)
{
	int healAmount = (rand() % 6) + 5;
	target.heal(healAmount);
	std::println("{} used HEALING POTION and restored {} HP!", target.getName(), healAmount);
}