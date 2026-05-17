#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Hero.h"
class User
{
private:
	std::string username;
	std::string password;
	int totalXp;
	int currentXp;
	std::vector<std::unique_ptr<Hero>> heroes;
	//items
	int battlesPlayed;
	int battlesWon;
public:
	User(const std::string& name, const std::string& pass);

	const std::string& getUsername() const;
	bool checkPassword(const std::string& inputPass) const;
	int getTotalXp() const;
	int getCurrentXp() const;

	void addGamePlayed();
	void addWin();
	void addXp(int xpToAdd);
	void removeXp(int xpToRemove);

	void addHero(std::unique_ptr<Hero> newHero);
	Hero* getHero(size_t index);
	size_t getHeroCount() const;
};

