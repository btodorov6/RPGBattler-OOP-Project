#pragma once
#include "Item.h"
class Blade final : public Item
{
	std::string getName() override;

	void use(Hero& target) override;
};
