#include "SystemManager.h"

#include <fstream>
#include <print>
#include <iostream>
#include <algorithm>

#include "Item.h"
#include "HealingPotion.h"
#include "Blade.h"
#include "Mirror.h"
#include "Ray.h"
#include "Shield.h"
#include "Mage.h"
#include "Archer.h"
#include "Warrior.h"
#include "BattleManager.h"

const std::string BLUE = "\033[36m";
const std::string RED = "\033[91m";
const std::string GREEN = "\033[32m";
const std::string RESET = "\033[0m";
const std::string GOLD = "\033[33m";
SystemManager::SystemManager()
	:loggedInPlayer1(nullptr), loggedInPlayer2(nullptr)
{
	loadFromFile();
}

SystemManager& SystemManager::getSystemManager()
{
	static SystemManager sm;
	return sm;
}

User* SystemManager::findUser(const std::string& username)
{
    for (auto& user : allUsers)
    {
        if (user.getUsername() == username) return &user;
    }
    return nullptr;
}

void SystemManager::run()
{
    while (true)
    {
        clearConsole();
        std::print("{}",RESET);

        std::println("{}---------------------------------",GOLD);
        std::println("           RPG BATTLER           ");
        std::println("---------------------------------{}",RESET);
        std::println("Logged Player 1: {}{}{}",BLUE, loggedInPlayer1 ? loggedInPlayer1->getUsername() : "None", RESET);
        std::println("Logged Player 2: {}{}{}",RED, loggedInPlayer2 ? loggedInPlayer2->getUsername() : "None", RESET);
        std::println("---------------------------------");
        std::println("1. Register New User");
        std::println("2. Login User");
        std::println("3. Open Leaderboard");
        std::println("4. Open Shop (Spend XP)");
        std::println("5. START BATTLE!");
        std::println("6. Logout / Clear Players");
        std::println("7. Save & Exit");
        std::print("Choose option: ");

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::println("{}Invalid input! Please enter a number.{}", RED, RESET);
            waitOnInput();
            continue;
        }

        switch (choice)
        {
        case 1:
            clearConsole();
            std::println("Registering new user...");
            registerUser(); 
            break;
        case 2: 
            clearConsole();
            std::println("Logging existing user...");
            loginMenu(); 
            break;
        case 3: 
            clearConsole();

            showLeaderboard();

            waitOnInput();
            break;
        case 4:
            if (!loggedInPlayer1) 
            {
                clearConsole();

                std::println("{}Please login at least Player 1 to use the shop.{}", RED, RESET);
                
                waitOnInput();
            }
            else 
            {
                clearConsole();

                std::println("Which player wants to shop? 1. {} | 2. {}",loggedInPlayer1->getUsername(),
                    loggedInPlayer2 ? loggedInPlayer2->getUsername() : "Not logged");
                int shopChoice;
                std::cin >> shopChoice;

                if (std::cin.fail())
                {
                    std::println("{}Invalid input! Please enter a number.{}", RED, RESET);
                    waitOnInput();
                    continue;
                }

                if (shopChoice == 1)
                    shopMenu(*loggedInPlayer1);
                else if (shopChoice == 2 && loggedInPlayer2 != nullptr)
                    shopMenu(*loggedInPlayer2);
                else
                {
                    std::println("{}Invalid input! That player is not logged in or doesn't exist.{}", RED, RESET);
                    waitOnInput();
                    continue;
                }
            }
            break;
        case 5:
            startBattleMenu();
            break;
        case 6:
            clearConsole();

            loggedInPlayer1 = nullptr;
            loggedInPlayer2 = nullptr;
            std::println("{}Players logged out.{}", GREEN, RESET);

            waitOnInput();
            break;
        case 7:
            clearConsole();
            saveToFile();
            std::println("{}Data saved successfully. Goodbye!{}", GREEN, RESET);
            return;
        default: 
            clearConsole();
            std::println("{}Invalid option.{}",RED,RESET); 
            waitOnInput();
            break;
        }
    }
}

void SystemManager::registerUser()
{
    std::string username, password;
    std::print("Enter username: ");
    std::cin >> username;
    std::print("Enter password: ");
    std::cin >> password;

    if (findUser(username) != nullptr) {
        std::println("{}Error: Username already exists!{}",RED,RESET);
        waitOnInput();
        return;
    }

    User newUser(username, password);

    std::string p1Name = "";
    std::string p2Name = "";
    if (loggedInPlayer1 != nullptr)
    {
        p1Name = loggedInPlayer1->getUsername();
    }
    if (loggedInPlayer2 != nullptr)
    {
        p2Name = loggedInPlayer2->getUsername();
    }

    allUsers.push_back(std::move(newUser));

    if (!p1Name.empty())
        loggedInPlayer1 = findUser(p1Name);
    if (!p2Name.empty()) 
        loggedInPlayer2 = findUser(p2Name);

    std::println("{}Registration successful for {}!{}",GREEN, username,RESET);
    waitOnInput();
}

void SystemManager::loginMenu()
{
    std::string username, password;
    std::print("Enter username: ");
    std::cin >> username;
    std::print("Enter password: ");
    std::cin >> password;

    User* u = findUser(username);

    if (!u || u->getPassword() != password)
    {
        std::println("{}Invalid username or password!{}",RED,RESET);
        waitOnInput();
        return;
    }
    if (!loggedInPlayer1)
    {
        loggedInPlayer1 = u;
        std::println("{}{} logged in as Player1{}",GREEN, username,RESET);
        waitOnInput();
    }
    else if (!loggedInPlayer2)
    {
        if (loggedInPlayer1 == u)
        {
            std::println("{}This user is already logged in as Player 1!{}",RED,RESET);
            waitOnInput();
            return;
        }
        loggedInPlayer2 = u;
        std::println("{}{} logged in as Player2{}", GREEN, username, RESET);
        waitOnInput();
    }
    else
    {
        std::println("{}Both player slots are full! Logout first.{}",RED,RESET);
        waitOnInput();
    }
}

void SystemManager::showLeaderboard()
{
    if (allUsers.empty()) {
        std::println("{}No registered users yet.{}",RED,RESET);
        waitOnInput();
        return;
    }

    std::vector<User*> sorted;

    for (auto& user : allUsers)
    {
        sorted.push_back(&user);
    }

    std::sort(sorted.begin(), sorted.end(), [](const User* a, const User* b) 
        {
        if (a->getWins() != b->getWins()) return a->getWins() > b->getWins();

        if (a->getTotalXp() != b->getTotalXp()) return a->getTotalXp() > b->getTotalXp();

        return a->getWinRate() > b->getWinRate(); 
        }
    );

    std::println("\n=== GLOBAL LEADERBOARD ===");
    std::println("{:<5} {:<15} {:<10} {:<10} {:<10}", "Pos", "Username", "Wins", "Total XP", "Win Rate");

    int position = 1;
    for (const auto& user : sorted) {
        std::println("{:<5} {:<15} {:<10} {:<10} {:.2f}%",
            position, user->getUsername(), user->getWins(), user->getTotalXp(), user->getWinRate() * 100);
        position++;
    }
}

void SystemManager::shopMenu(User& user)
{
    while (true)
    {
        clearConsole();
        std::println("\n--- SHOP FOR {} (Available XP: {}) ---", user.getUsername(), user.getCurrentXp());
        std::println("1. Buy Healing Potion (30 XP)");
        std::println("2. Buy Blade (50 XP)");
        std::println("3. Buy Mirror (80 XP)");
        std::println("4. Buy Ray (90 XP)");
        std::println("5. Buy Shield (100 XP)");
        std::println("6. Buy New Hero (50 XP)");
        std::println("7. Upgrade Hero Level (100 XP)");
        std::println("0. Exit Shop");
        std::print("Choice: ");
        int choice; 
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::println("{}Invalid input! Please enter a number.{}", RED, RESET);
            waitOnInput();
            continue;
        }
        if (choice == 0) return;

        if (choice == 1 && user.getCurrentXp() >= 30)
        {
            user.removeXp(30);
            user.addItem(std::make_unique<HealingPotion>());
            std::println("{}Bought HEALING POTION!{}",GREEN,RESET);
            waitOnInput();
        }
        else if (choice == 2 && user.getCurrentXp() >= 50)
        {
            user.removeXp(50);
            user.addItem(std::make_unique<Blade>());
            std::println("{}Bought BLADE!{}", GREEN, RESET);
            waitOnInput();
        }
        else if (choice == 3 && user.getCurrentXp() >= 80)
        {
            user.removeXp(80);
            user.addItem(std::make_unique<Mirror>());
            std::println("{}Bought MIRROR!{}", GREEN, RESET);
            waitOnInput();
        }
        else if (choice == 4 && user.getCurrentXp() >= 90)
        {
            user.removeXp(90);
            user.addItem(std::make_unique<Ray>());
            std::println("{}Bought RAY!{}", GREEN, RESET);
            waitOnInput();
        }
        else if (choice == 5 && user.getCurrentXp() >= 100)
        {
            user.removeXp(100);
            user.addItem(std::make_unique<Shield>());
            std::println("{}Bought Shield!{}", GREEN, RESET);
            waitOnInput();
        }
        else if (choice == 6 && user.getCurrentXp() >= 50)
        {
            std::println("Choose hero type: 1. Warrior | 2. Mage | 3. Archer");
            int type; 
            std::cin >> type;

            if (std::cin.fail())
            {
                std::println("{}Invalid input! Please enter a number.{}", RED, RESET);
                waitOnInput();
                continue;
            }

            std::print("Enter hero name: ");
            std::string heroName; std::cin >> heroName;

            user.removeXp(50);
            if (type == 2) user.addHero(std::make_unique<Mage>(heroName));
            else if (type == 3) user.addHero(std::make_unique<Archer>(heroName));
            else user.addHero(std::make_unique<Warrior>(heroName));
            std::println("{}New hero bought!{}", GREEN, RESET);
            waitOnInput();
        }
        else if (choice == 7 && user.getCurrentXp() >= 100)
        {
            user.removeXp(100);
            std::println("\nSelect a hero to upgrade:");
            user.printHeroes();
            std::print("Enter hero number (0 to cancel): ");

            int heroChoice;
            std::cin >> heroChoice;

            if (std::cin.fail())
            {
                std::println("{}Invalid input! Please enter a number.{}", RED, RESET);
                waitOnInput();
                continue;
            }

            if (heroChoice == 0) continue;

            Hero* selectedHero = user.getHero(heroChoice - 1);

            if (selectedHero == nullptr)
            {
                std::println("{}Invalid hero selection!{}",RED,RESET);
                waitOnInput();
                continue;
            }

            std::println("\nChoose upgrade effect for {}:", selectedHero->getName());
            std::println("1. Permanently increase Max HP by {}+2{}", GREEN, RESET);
            std::println("2. Permanently increase Max Damage upper limit by {}+1{}",  GREEN, RESET);
            std::print("Choice: ");

            int statChoice;
            std::cin >> statChoice;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                statChoice = 1;
            }

            if (statChoice == 2)
            {
                selectedHero->levelUpMaxDmg();
                std::println("{}{}'s Max Damage is now increased by 1!{}", GREEN, selectedHero->getName(), RESET);
                waitOnInput();
            }
            else
            {
                selectedHero->levelUpMaxHp();
                std::println("{}{}'s Max HP is now increased by 2!{}", GREEN, selectedHero->getName(), RESET);
                waitOnInput();
            }

        }
        else {
            std::println("{}Not enough XP or invalid choice!{}",RED,RESET);
            waitOnInput();
        }
    }
}

void SystemManager::startBattleMenu()
{
    if (loggedInPlayer1 == nullptr || loggedInPlayer2 == nullptr)
    {
        std::println("{}Both players must be logged in to start the battle!{}",RED,RESET);
        waitOnInput();
        return;
    }

    std::println("\n{} (Player 1), choose your hero for the battle:", loggedInPlayer1->getUsername());
    loggedInPlayer1->printHeroes();
    std::print("Enter hero number: ");
    int h1Choice;
    std::cin >> h1Choice;

    if (std::cin.fail())
    {
        std::println("{}Invalid input! Please enter a number.{}", RED, RESET);
        waitOnInput();
        return;
    }

    Hero* h1 = loggedInPlayer1->getHero(h1Choice - 1);

    std::println("\n{} (Player 2), choose your hero for the battle:", loggedInPlayer2->getUsername());
    loggedInPlayer2->printHeroes();
    std::print("Enter hero number: ");
    int h2Choice;
    std::cin >> h2Choice;
    Hero* h2 = loggedInPlayer2->getHero(h2Choice - 1);

    if (h1 != nullptr && h2 != nullptr)
    {
        BattleManager::getBattleManager().startBattle(*loggedInPlayer1, *loggedInPlayer2, *h1, *h2);

        h1->heal(h1->getMaxHp());
        h2->heal(h2->getMaxHp());
        std::println("\n{}Heroes have been fully healed back to maximum HP!{}", GREEN, RESET);
    }
    else
    {
        std::println("{}Invalid hero selection! Battle canceled.{}",RED,RESET);
        waitOnInput();
    }
}

void SystemManager::saveToFile()
{
    std::ofstream ofs("gamedata.txt");
    if (!ofs.is_open()) return;

    ofs << allUsers.size() << "\n";
    for (const auto& user : allUsers)
    {
        user.serialize(ofs);
    }
    ofs.close();
}

void SystemManager::loadFromFile()
{
    std::ifstream ifs("gamedata.txt");
    if (!ifs.is_open()) return;

    size_t userCount;
    if (!(ifs >> userCount)) return;

    allUsers.clear();
    for (size_t i = 0; i < userCount; ++i)
    {
        User tempUser;
        tempUser.deserialize(ifs);
        allUsers.push_back(std::move(tempUser));
    }
    ifs.close();
}

void SystemManager::clearConsole() const
{
    std::print("\033[2J\033[H");//clear console
}

void SystemManager::waitOnInput() const
{
    if (std::cin.fail())
    {
        std::cin.clear();
    }

    std::println("\npress Enter to return to main menu...");
    std::cin.ignore(10000, '\n');
    std::cin.get();
}