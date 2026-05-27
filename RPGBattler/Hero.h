#pragma once
#include <string>
class Hero
{
protected:
	std::string name;
	int maxHP;
	int maxDmg;
	int currentHP;
	int level;
	bool isBladeActive;
	bool isAffectedByMirror;
public:
	Hero(const std::string& heroName, int heroMaxHp, int heroMaxDmg);
	virtual ~Hero() = default;
	virtual void TakeDamage(int damage);
	virtual int Attack() = 0;

	bool isAlive() const;
	std::string getName() const;
	int getCurrentHp() const;
	int getMaxHp() const;
	int getLevel() const;

	void levelUpMaxHp();
	void levelUpMaxDmg();

	void heal(int amountToHeal);

	void activateBlade();
	void hitByMirror();

	int getMaxDmg() const;
	void loadStats(int newLevel, int newMaxHp, int newMaxDmg);
	virtual char getHeroType() const = 0;
};

