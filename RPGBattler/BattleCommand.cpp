#include "BattleCommand.h"
#include "SystemManager.h"

BattleCommand::BattleCommand(SystemManager& m) : manager(m) {}

void BattleCommand::execute()
{
    manager.startBattleMenu();
}