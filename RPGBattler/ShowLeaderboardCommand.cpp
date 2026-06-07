#include "ShowLeaderboardCommand.h"
#include "SystemManager.h"

ShowLeaderboardCommand::ShowLeaderboardCommand(SystemManager& m) : manager(m) {}

void ShowLeaderboardCommand::execute() {
    manager.clearConsole();
    manager.showLeaderboard();
    manager.waitOnInput();
}