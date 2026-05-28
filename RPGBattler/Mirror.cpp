#include "Mirror.h"
#include <print>
std::string Mirror::getName()
{
	return "Mirror";
}
void Mirror::use(Hero& target)//mirror blocks the special ability of the enemy character for the next turn
{
	target.hitByMirror();
	std::println("MIRROR effect applied to {}! Their next special ability is blocked.", target.getName());
}