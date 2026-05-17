#pragma once
#include "Hero.h"
class Archer final : public Hero
{
public: 
	Archer(const std::string& heroName);
	int Attack() override;
};

