#include "BattleManager.h"
#include <iostream>
#include <print>
#include <cstdlib>

//COLOURS
const std::string RESET = "\033[0m";
const std::string PLAYER1_COLOUR = "\033[36m";
const std::string PLAYER2_COLOUR = "\033[31m";
const std::string REACTION_COLOUR = "\033[33m";
BattleManager& BattleManager::getBattleManager()
{
	static BattleManager bm;
	return bm;
}

void BattleManager::playTurn(User& activePlayer, User& targetPlayer, Hero& activeHero, Hero& targetHero, const std::string& playerColor, const std::string& targetColor) //turn logic
{
	std::println("\n{}{}'s turn.",playerColor, activeHero.getName());
	
	while (true)
	{
		std::println("1.Attack");
		std::println("2.Inventory");

		std::print("Choice:");
		int choice;
		std::cin >> choice;

		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(10000, '\n');
			std::println("Invalid input! Please enter a number.");
			continue;
		}

		if (choice == 1)
		{
			int dmg = activeHero.Attack();

			if (dmg > 0 && targetPlayer.hasItem("Shield"))
			{
				std::print("\n{}{}{} has attacked {} for {}dmg but {} has a SHIELD. Do you want to use it? (y/n) : ", targetColor, activeHero.getName(), playerColor, targetHero.getName(), dmg, targetPlayer.getUsername());
				char useShield;
				std::cin >> useShield;
				if (useShield == 'y' ||useShield == 'Y')
				{
					targetPlayer.consumeItem("Shield");
					dmg = 0;
					std::println("{} used a SHIELD and blocked the attack!{}", targetPlayer.getUsername(),playerColor);
				}

				std::print("{}", playerColor);
			}

			if (dmg > 0)
			{
				std::println("{} attacked for {}dmg!", activeHero.getName(), dmg);
				targetHero.TakeDamage(dmg);
				std::println("{} is now on {}hp", targetHero.getName(), targetHero.getCurrentHp());
			}
			return;
		}
		else if (choice == 2)
		{
			std::println("{}'s Inventory: ",activePlayer.getUsername());
			activePlayer.printInventory();
			std::println("0.Cancel");
			std::print("Choose item: ");
			int itemChoice;
			std::cin >> itemChoice;

			if (std::cin.fail())
			{
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::println("Invalid input! Please enter a number.");
				continue;
			}

			if (itemChoice == 0) continue;

			std::string itemName = activePlayer.getItemNameFromMenu(itemChoice);

			if (itemName == "")
			{
				std::println("Invalid choice try again...");
				continue;
			}
			if (itemName == "Shield" || itemName == "Ray") {
				std::println("{} can only be used automatically as a reaction!", itemName);
				continue;
			}
			if (itemName == "Mirror")
			{
				if (targetPlayer.hasItem("Ray"))
				{
					std::print("\n{}{}{} has used MIRROR, but {} has a RAY! Counter it? (y/n): ", targetColor, activePlayer.getUsername(), playerColor, targetPlayer.getUsername());
					char useRay;
					std::cin >> useRay;
					if (useRay == 'y' || useRay == 'Y')
					{
						targetPlayer.consumeItem("Ray");
						activePlayer.consumeItem("Mirror");
						std::println("{} used RAY! The MIRROR shattered.{}", targetPlayer.getUsername(),playerColor);
						std::print("{}", playerColor);
						return;
					}
					std::print("{}", playerColor);
				}
				activePlayer.useItemOnTarget("Mirror", targetHero);
			}
			else
			{
				activePlayer.useItemOnTarget(itemName, activeHero);
			}
			return;
		}
		else
		{
			std::println("Invalid Input...");
		}
	}
}

void BattleManager::startBattle(User& player1, User& player2, Hero& hero1, Hero& hero2)
{
	std::print("\033[2J\033[H");//clear console
	std::print("{}", RESET);
	std::println("Battle has begun!!!");
	bool isPlayer1Turn = rand() % 2;

	while (hero1.isAlive() && hero2.isAlive()) //battle loop
	{
		if (isPlayer1Turn)
		{
			playTurn(player1, player2, hero1, hero2,PLAYER1_COLOUR,PLAYER2_COLOUR);
		}
		else
		{
			playTurn(player2, player1, hero2, hero1,PLAYER2_COLOUR,PLAYER1_COLOUR);
		}
		isPlayer1Turn = !isPlayer1Turn;
		
	}
	std::print("{}",REACTION_COLOUR);
	if (hero1.isAlive())
	{
		std::println("{} Won!",hero1.getName());
		player1.addWin();
		player1.addGamePlayed();
		player2.addGamePlayed();

		player1.addXp(10);
		player2.addXp(5);
	}
	else
	{
		std::println("{} Won!", hero2.getName());
		player2.addWin();
		player1.addGamePlayed();
		player2.addGamePlayed();

		player2.addXp(10);
		player1.addXp(5);
	}
	std::print("{}", RESET);

	std::println("\npress Enter to return to main menu...");
	std::cin.ignore(10000, '\n');
	std::cin.get();
}
