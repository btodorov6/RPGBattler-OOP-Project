#include "LogoutCommand.h"
#include "SystemManager.h"

LogoutCommand::LogoutCommand(SystemManager& m) : manager(m) {}

void LogoutCommand::execute()
{
    manager.logOutPlayers();
}