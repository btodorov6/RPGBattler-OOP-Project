#include "BattleManager.h"
#include <iostream>
#include <print>

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

void BattleManager::playTurn(User& activePlayer, User& targetPlayer, Hero& activeHero, Hero& targetHero, const std::string& playerColour) //turn logic
{
	std::println("\n{}{}'s turn.",playerColour, activeHero.getName());
	
	while (true)
	{
		std::println("1.Attack");
		std::println("2.Inventory");

		std::print("Choice:");
		int choice;
		std::cin >> choice;

		if (choice == 1)
		{
			int dmg = activeHero.Attack();

			if (dmg > 0 && targetPlayer.hasItem("Shield"))
			{
				std::print("{}{} has attacked {} for {}dmg but {} has a SHIELD. Do you want to use it? (y/n) : ",REACTION_COLOUR, activeHero.getName(),targetHero.getName(),dmg,targetPlayer.getUsername());
				char useShield;
				std::cin >> useShield;
				if (useShield == 'y' ||useShield == 'Y')
				{
					targetPlayer.consumeItem("Shield");
					dmg = 0;
					std::println("{} used a SHIELD and blocked the attack!{}", targetPlayer.getUsername(),playerColour);
				}
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
					std::print("{}{} has used MIRROR, but {} has a RAY! Counter it? (y/n): ",REACTION_COLOUR, activePlayer.getUsername(),targetPlayer.getUsername());
					char useRay;
					std::cin >> useRay;
					if (useRay == 'y' || useRay == 'Y')
					{
						targetPlayer.consumeItem("Ray");
						activePlayer.consumeItem("Mirror");
						std::println("{} used RAY! The MIRROR shattered.{}", targetPlayer.getUsername(),playerColour);
						return;
					}
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
	std::println("Battle has begun!!!");
	bool isPlayer1Turn = rand() % 2;

	while (hero1.isAlive() && hero2.isAlive()) //battle loop
	{
		if (isPlayer1Turn)
		{
			playTurn(player1, player2, hero1, hero2,PLAYER1_COLOUR);
		}
		else
		{
			playTurn(player2, player1, hero2, hero1,PLAYER2_COLOUR);
		}
		isPlayer1Turn = !isPlayer1Turn;
		
	}
	std::print("{}",REACTION_COLOUR);
	if (hero1.isAlive())
	{
		std::println("{} Won!",hero1.getName());
		//give 10xp
	}
	else
	{
		std::println("{} Won!", hero2.getName());
		//give 5xp
	}

}
