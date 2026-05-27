#pragma once
#include <string>
#include <vector>
#include <memory>
#include <fstream> 

#include "Hero.h"
#include "Item.h"
class User
{
private:
	std::string username;
	std::string password;
	int totalXp;
	int currentXp;
	std::vector<std::unique_ptr<Hero>> heroes;
	std::vector<std::unique_ptr<Item>> inventory;
	int battlesPlayed;
	int battlesWon;
public:
	User(const std::string& name, const std::string& pass);
	User(User&&) noexcept = default;

	const std::string& getUsername() const;
	bool checkPassword(const std::string& inputPass) const;
	int getTotalXp() const;
	int getCurrentXp() const;

	void addGamePlayed();
	void addWin();
	void addXp(int xpToAdd);
	void removeXp(int xpToRemove);

	void printHeroes() const;
	void addHero(std::unique_ptr<Hero> newHero);
	Hero* getHero(size_t index);
	size_t getHeroCount() const;

	void printInventory();

	bool hasItem(const std::string& name) const;
	void consumeItem(const std::string& name);
	void useItemOnTarget(const std::string& name, Hero& target);
	std::string getItemNameFromMenu(int choice) const;
	std::string getPassword() const;
	int getWins() const;
	double getWinRate() const;
	void addItem(std::unique_ptr<Item> item);

	void serialize(std::ofstream& ofs) const;
	void deserialize(std::ifstream& ifs);
};

