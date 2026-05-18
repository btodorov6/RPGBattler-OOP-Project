#include "Shield.h"

std::string Shield::getName()
{
	return "Shield";
}

void Shield::use(Hero& target)
{
	target.activateShield();
}