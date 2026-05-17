#include "BattleManager.h"
#include <iostream>
#include <print>
BattleManager& BattleManager::getBattleManager()
{
	static BattleManager bm;
	return bm;
}

void BattleManager::playTurn(/*User& player1, User& player2, */Hero& activeHero, Hero& targetHero) //turn logic
{
	std::println("\n{}'s turn.", activeHero.getName());
	std::println("1.Attack");
	//std::println("2.Inventory");

	std::print("Choice:");
	int choice;
	std::cin >> choice;

	if (choice == 1)
	{
		int dmg = activeHero.Attack();
		std::println("{} attacked for {}dmg!", activeHero.getName(),dmg);
		targetHero.TakeDamage(dmg);		
		std::println("{} is now on {}hp", targetHero.getName(), targetHero.getCurrentHp());
	}
}

void BattleManager::startBattle(/*User& player1, User& player2, */Hero& hero1, Hero& hero2)
{
	std::println("Battle has begun!!!");
	bool isPlayer1Turn = rand() % 2;

	while (hero1.isAlive() && hero2.isAlive()) //battle loop
	{
		if (isPlayer1Turn)
		{
			playTurn(hero1, hero2);
		}
		else
		{
			playTurn(hero2, hero1);
		}
		isPlayer1Turn = !isPlayer1Turn;
		
	}
	if (hero1.isAlive())
	{
		std::println("{} Won!",hero1.getName());
	}
	else
	{
		std::println("{} Won!", hero2.getName());
	}
	//give exp	

}
