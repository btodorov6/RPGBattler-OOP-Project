#include "Ray.h"

std::string Ray::getName()
{
	return "Ray";
}

void Ray::use(Hero& target)
{
	target.cleansedFromRay();
}