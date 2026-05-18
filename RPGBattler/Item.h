#pragma once
#include "Hero.h"

class Item
{
	public:
		virtual ~Item() = default;
		virtual std::string getName() = 0;

		virtual void use(Hero& target) = 0;
};

