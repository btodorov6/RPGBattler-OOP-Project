#pragma once
#include "Hero.h"
class BattleManager
{
private:

	BattleManager() = default;
	void playTurn(/*User& player1, User& player2, */Hero& activeHero, Hero& targetHero);

public:

	BattleManager(const BattleManager&) = delete;
	BattleManager& operator=(const BattleManager&) = delete;

	static BattleManager& getBattleManager();

	void startBattle(/*User& player1, User& player2, */Hero& hero1, Hero& hero2);
};

