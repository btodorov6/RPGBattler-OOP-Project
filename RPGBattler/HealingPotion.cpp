#include "HealingPotion.h"

std::string HealingPotion::getName()
{
	return "Healing Potion";
}

void HealingPotion::use(Hero& target)
{
	int healAmount = (rand() % 6) + 5;
	target.heal(healAmount);
}