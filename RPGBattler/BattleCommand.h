#pragma once
#include "Command.h"

class SystemManager;

class BattleCommand : public Command
{
private:
    SystemManager& manager;
public:
    BattleCommand(SystemManager& m);
    void execute() override;
};