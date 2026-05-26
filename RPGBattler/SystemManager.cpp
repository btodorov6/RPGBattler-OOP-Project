#include "SystemManager.h"
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
        std::println("---------------------------------");
        std::println("           RPG BATTLER           ");
        std::println("---------------------------------");
        std::println("Logged Player 1: {}", loggedInPlayer1 ? loggedInPlayer1->getUsername() : "None");
        std::println("Logged Player 2: {}", loggedInPlayer2 ? loggedInPlayer2->getUsername() : "None");
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
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            registerUser(); 
            break;
        case 2: 
            loginMenu(); 
            break;
        case 3: 
            showLeaderboard(); 
            break;
        case 4:
            if (!loggedInPlayer1) 
            {
                std::println("Please login at least Player 1 to use the shop.");
            }
            else 
            {
                std::println("Which player wants to shop? 1. {} | 2. {}",loggedInPlayer1->getUsername(),
                    loggedInPlayer2 ? loggedInPlayer2->getUsername() : "Not logged");
                int shopChoice;
                std::cin >> shopChoice;
                if (shopChoice == 2 && loggedInPlayer2) shopMenu(*loggedInPlayer2);
                else shopMenu(*loggedInPlayer1);
            }
            break;
        case 5:
            startBattleMenu();
            break;
        case 6:
            loggedInPlayer1 = nullptr;
            loggedInPlayer2 = nullptr;
            std::println("Players logged out.");
            break;
        case 7:
            saveToFile();
            std::println("Data saved successfully. Goodbye!");
            return;
        default: std::println("Invalid option."); break;
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
        std::println("Error: Username already exists!");
        return;
    }

    User newUser(username, password);
    allUsers.push_back(std::move(newUser));
    std::println("Registration successful for {}!", username);
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
        std::println("Invalid username or password!");
        return;
    }
    if (!loggedInPlayer1)
    {
        loggedInPlayer1 = u;
        std::println("{} logged in as Player1", username);
    }
    else if (!loggedInPlayer2)
    {
        if (loggedInPlayer1 == u)
        {
            std::println("This user is already logged in as Player 1!");
            return;
        }
        loggedInPlayer2 = u;
        std::println("{} logged in as Player2", username);
    }
    else
    {
        std::println("Both player slots are full! Logout first.");
    }
}

void SystemManager::showLeaderboard()
{
    if (allUsers.empty()) {
        std::println("No registered users yet.");
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
        if (choice == 0) return;

        if (choice == 1 && user.getCurrentXp() >= 30)
        {
            user.removeXp(30);
            user.addItem(std::make_unique<HealingPotion>());
            std::println("Bought HEALING POTION!");       
        }
        else if (choice == 2 && user.getCurrentXp() >= 50)
        {
            user.removeXp(50);
            user.addItem(std::make_unique<Blade>());
            std::println("Bought BLADE!");
        }
        else if (choice == 3 && user.getCurrentXp() >= 80)
        {
            user.removeXp(80);
            user.addItem(std::make_unique<Mirror>());
            std::println("Bought MIRROR!");
        }
        else if (choice == 4 && user.getCurrentXp() >= 90)
        {
            user.removeXp(90);
            user.addItem(std::make_unique<Ray>());
            std::println("Bought RAY!");
        }
        else if (choice == 5 && user.getCurrentXp() >= 100)
        {
            user.removeXp(100);
            user.addItem(std::make_unique<Shield>());
            std::println("Bought Shield!");
        }
        else if (choice == 6 && user.getCurrentXp() >= 50)
        {
            std::println("Choose hero type: 1. Warrior | 2. Mage | 3. Archer");
            int type; std::cin >> type;
            std::print("Enter hero name: ");
            std::string heroName; std::cin >> heroName;

            user.removeXp(50);
            if (type == 2) user.addHero(std::make_unique<Mage>(heroName));
            else if (type == 3) user.addHero(std::make_unique<Archer>(heroName));
            else user.addHero(std::make_unique<Warrior>(heroName));
            std::println("New hero bought!");
        }
        else if (choice == 7 && user.getCurrentXp() >= 100)
        {
            user.removeXp(100);
            std::println("\nSelect a hero to upgrade:");
            user.printHeroes();
            std::print("Enter hero number (0 to cancel): ");

            int heroChoice;
            std::cin >> heroChoice;

            if (heroChoice == 0) continue;

            Hero* selectedHero = user.getHero(heroChoice - 1);

            if (selectedHero == nullptr)
            {
                std::println("Invalid hero selection!");
                continue;
            }

            std::println("\nChoose upgrade effect for {}:", selectedHero->getName());
            std::println("1. Permanently increase Max HP by +2");
            std::println("2. Permanently increase Max Damage upper limit by +1");
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
                std::println("{}'s Max Damage is now increased by 1!", selectedHero->getName());
            }
            else
            {
                selectedHero->levelUpMaxHp();
                std::println("{}'s Max HP is now increased by 2!", selectedHero->getName());
            }

        }
        else {
            std::println("Not enough XP or invalid choice!");
        }
    }
}

void SystemManager::startBattleMenu()
{
    if (loggedInPlayer1 == nullptr || loggedInPlayer2 == nullptr)
    {
        std::println("Both players must be logged in to start the battle!");
        return;
    }

    std::println("\n{} (Player 1), choose your hero for the battle:", loggedInPlayer1->getUsername());
    loggedInPlayer1->printHeroes();
    std::print("Enter hero number: ");
    int h1Choice;
    std::cin >> h1Choice;
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
        std::println("\nHeroes have been fully healed back to maximum HP!");
    }
    else
    {
        std::println("Invalid hero selection! Battle canceled.");
    }
}

void SystemManager::saveToFile()
{
}

void SystemManager::loadFromFile()
{
}