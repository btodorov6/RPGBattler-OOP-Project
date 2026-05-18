#include "User.h"
#include "Hero.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "Item.h"
#include "HealingPotion.h"
#include "Blade.h"
#include "Mirror.h"
#include "Ray.h"
#include "Shield.h"
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
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		choice = -1;
	}

	std::cin.ignore();
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

	std::println("Choose starting item:");
	std::println("1.Blade|2.Healing potion|3.Mirror|4.Ray|5.Shield");
	std::print("Choose: ");
	std::cin >> choice;
	if (std::cin.fail())
	{
		std::cin.clear();
		std::cin.ignore(10000, '\n');
		choice = -1;
	}

	switch (choice)
	{
	case 1:
		inventory.push_back(std::make_unique<Blade>());
		break;
	case 2:
		inventory.push_back(std::make_unique<HealingPotion>());
		break;
	case 3:
		inventory.push_back(std::make_unique<Mirror>());
		break;
	case 4:
		inventory.push_back(std::make_unique<Ray>());
		break;
	case 5:
		inventory.push_back(std::make_unique<Shield>());
		break;
	default:
		inventory.push_back(std::make_unique<HealingPotion>());
		std::println("Invalid input so Health potion chosen.");
		break;
	}
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

struct ItemCount {
	std::string name;
	int count;
};

void User::printInventory()
{
	if (inventory.empty())
	{
		std::println("Inventory is empty...");
		return;
	}

	std::vector<ItemCount> groupedItems;

	for (const auto& item : inventory)
	{
		bool found = false;
		for (auto& group : groupedItems)
		{
			if (group.name == item->getName())
			{
				group.count++;
				found = true;
				break;
			}
		}

		if (!found)
		{
			groupedItems.push_back({ item->getName(), 1 });
		}
	}

	int index = 1;
	for (const auto& group : groupedItems) {
		std::println("{}. {} (x{})", index, group.name, group.count);
		index++;
	}
}

bool User::hasItem(const std::string& itemName) const
{
	for (const auto& item : inventory)
	{
		if (item->getName() == itemName)
		{
			return true;
		}
	}
	return false;
}

void User::consumeItem(const std::string& itemName)
{
	for (auto it = inventory.begin();it != inventory.end();++it)
	{
		if ((*it)->getName() == itemName)
		{
			inventory.erase(it);
			return;
		}
	}
}

void User::useItemOnTarget(const std::string& itemName, Hero& target)
{
	for (auto it = inventory.begin();it != inventory.end();++it)
	{
		if ((*it)->getName() == itemName)
		{
			(*it)->use(target);
			inventory.erase(it);
			return;
		}
	}
}

std::string User::getItemNameFromMenu(int choice) const 
{
	std::vector<std::string> groupedNames;

	for (const auto& item : inventory) 
	{
		bool found = false;

		for (const auto& name : groupedNames) 
		{
			if (name == item->getName()) found = true;
		}

		if (!found) groupedNames.push_back(item->getName());
	}

	if (choice > 0 && choice <= groupedNames.size()) 
	{
		return groupedNames[choice - 1];
	}
	return ""; 
}