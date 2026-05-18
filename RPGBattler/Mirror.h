#pragma once
#include "Item.h"
class Mirror final: public Item
{
	std::string getName() override;

	void use(Hero& target) override;
};

