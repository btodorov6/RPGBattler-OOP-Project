#pragma once
#include "Item.h"
class Shield : public Item
{
	std::string getName() override;

	void use(Hero& target) override;
};

