#include "ExitCommand.h"
#include "SystemManager.h"
#include <print>
ExitCommand::ExitCommand(SystemManager& m) : manager(m) {}

void ExitCommand::execute() {
    manager.clearConsole();
    manager.saveToFile();
    std::println("{}Data saved successfully. Goodbye!{}", "\033[32m", "\033[0m");
    manager.stopRunning();
}