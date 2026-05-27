#pragma once
#include <vector>
#include <string>
#include "User.h"

class SystemManager
{
private:
    std::vector<User> allUsers;
    User* loggedInPlayer1;
    User* loggedInPlayer2;

    SystemManager();

    void registerUser();
    void loginMenu();
    void showLeaderboard();
    void shopMenu(User& user);
    void startBattleMenu();

    void saveToFile();
    void loadFromFile();

    User* findUser(const std::string& username);
public:
    
    static SystemManager& getSystemManager();

    SystemManager(const SystemManager&) = delete;
    SystemManager& operator=(const SystemManager&) = delete;

    void run();

    void clearConsole() const;
    void waitOnInput() const;
};