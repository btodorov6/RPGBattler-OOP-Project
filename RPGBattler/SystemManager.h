#pragma once
#include <vector>
#include <string>
#include "User.h"
#include "Command.h"

class SystemManager
{
private:
    std::vector<User> allUsers;
    User* loggedInPlayer1;
    User* loggedInPlayer2;

    SystemManager();

    void printConsole() const;

    void loadFromFile();

    User* findUser(const std::string& username);

    std::vector<std::unique_ptr<Command>> menuCommands;
    bool isRunning;
public:
    void stopRunning();
    
    static SystemManager& getSystemManager();

    SystemManager(const SystemManager&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;

    void run();

    void clearConsole() const;
    void waitOnInput() const;

    void registerUser();
    void loginMenu();
    void showLeaderboard();
    void shopMenu();
    void startBattleMenu();
    void logOutPlayers();
    void saveToFile();
};