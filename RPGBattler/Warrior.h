#pragma once
#include "Hero.h"
class Warrior final : public Hero
{
private:

public:
	Warrior(const std::string& heroName);
	int Attack() override;
	void TakeDamage(int damage) override;
	char getHeroType() const override;
};

