#include "Blade.h"
std::string Blade::getName()
{
	return "Blade";
}

void Blade::use(Hero& target)
{
	target.activateBlade();
}