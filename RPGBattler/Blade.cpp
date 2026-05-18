#include "Blade.h"
#include <print>
std::string Blade::getName()
{
	return "Blade";
}

void Blade::use(Hero& target)
{
	target.activateBlade();
	std::println("{} sharpened their BLADE! Next attack will deal double damage.", target.getName());
}