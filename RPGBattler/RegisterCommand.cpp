#include "RegisterCommand.h"
#include "SystemManager.h"
#include <print>

RegisterCommand::RegisterCommand(SystemManager& m) : manager(m) {}

void RegisterCommand::execute() {
    manager.clearConsole();
    std::println("Registering new user...");
    manager.registerUser();
}