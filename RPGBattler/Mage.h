#pragma once
#include "Hero.h"
class Mage final : public Hero
{
public:
	Mage(const std::string& heroName);
	int Attack() override;
};

