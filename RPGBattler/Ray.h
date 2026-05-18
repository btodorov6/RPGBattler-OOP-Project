#pragma once
#include "Item.h"
class Ray final : public Item
{
	std::string getName() override;

	void use(Hero& target) override;
};

