#include "Hero.h"

Hero::Hero(const std::string& heroName, int heroMaxHp, int heroMaxDmg)
	: name(heroName), maxDmg(heroMaxDmg), maxHP(heroMaxHp), currentHP(heroMaxHp), level(1),
	isBladeActive(false), isAffectedByMirror(false)
{
}
void Hero::TakeDamage(int damage)
{
	currentHP -= damage;
	if (currentHP <= 0)
	{
		currentHP = 0;
	}
}
bool Hero::isAlive() const
{
	return currentHP > 0;
}

std::string Hero::getName() const
{
	return name;
}

int Hero::getCurrentHp() const
{
	return currentHP;
}

int Hero::getMaxHp() const
{
	return maxHP;
}

int Hero::getLevel() const
{
	return level;
}

void Hero::levelUpMaxHp()
{
	maxHP += 2;
}

void Hero::levelUpMaxDmg()
{
	maxDmg += 1;
}

void Hero::heal(int amount)
{
	currentHP += amount;
	if (currentHP > maxHP)
	{
		currentHP = maxHP;
	}
}

void Hero::activateBlade()
{
	isBladeActive = true;
}

void Hero::hitByMirror()
{
	isAffectedByMirror = true;
}
