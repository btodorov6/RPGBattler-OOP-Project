#pragma once
#include "Item.h"
class HealingPotion final: public Item
{
	std::string getName() override;

	void use(Hero& target) override;
};

