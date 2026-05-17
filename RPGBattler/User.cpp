#include "User.h"
#include "Hero.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include <print>
#include <iostream>

User::User(const std::string& name, const std::string& pass)
	:username(name), password(pass), totalXp(0),currentXp(0),battlesPlayed(0),battlesWon(0)
{
	std::println("New User Created - {}", name);
	std::println("Choose starting Hero:");
	std::println("1.Warrior|2.Mage|3.Archer");
	std::print("Choose: ");
	int choice;
	std::cin >> choice;
	std::cin.clear();
	std::cin.ignore(10000, '\n');
	std::print("What is your hero called?: ");
	std::string heroName;
	std::getline(std::cin, heroName);

	std::unique_ptr<Hero> newHero;
	switch (choice)
	{
	case 1:
		newHero = std::make_unique<Warrior>(heroName);
		break;
	case 2:
		newHero = std::make_unique<Mage>(heroName);
		break;
	case 3:
		newHero = std::make_unique<Archer>(heroName);
		break;
	default:
		std::println("Invalid input so Warrior chosen.");
		newHero = std::make_unique<Warrior>(heroName);
		break;
	}
	addHero(std::move(newHero));
}

const std::string& User::getUsername() const
{
	return username;
}

bool User::checkPassword(const std::string& inputPass) const
{
	return password == inputPass;
}

int User::getTotalXp() const
{
	return totalXp;
}
int User::getCurrentXp() const
{
	return currentXp;
}

void User::addGamePlayed()
{
	battlesPlayed++;
}
void User::addWin()
{
	battlesWon++;
}
void User::addXp(int amount)
{
	totalXp += amount;
	currentXp += amount;
}
void User::removeXp(int amount)
{
	currentXp -= amount;
}

void User::addHero(std::unique_ptr<Hero> newHero)
{
	heroes.push_back(std::move(newHero));
}

Hero* User::getHero(size_t index)
{
	if (index >= heroes.size())
	{
		return nullptr;
	}
	return heroes[index].get();
}

size_t User::getHeroCount() const
{
	return heroes.size();
}