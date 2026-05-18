#include "Mirror.h"
std::string Mirror::getName()
{
	return "Mirror";
}
void Mirror::use(Hero& target)
{
	target.hitByMirror();
}