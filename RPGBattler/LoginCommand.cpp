#include "LoginCommand.h"
#include "SystemManager.h"
#include <print>

LoginCommand::LoginCommand(SystemManager& m) : manager(m) {}

void LoginCommand::execute()
{
    manager.clearConsole();
    std::println("Logging existing user...");
    manager.loginMenu();
}