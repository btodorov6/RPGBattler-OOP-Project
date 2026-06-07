#pragma once
#include "Command.h"

class SystemManager;

class ShowLeaderboardCommand : public Command
{
private:
    SystemManager& manager;
public:
    ShowLeaderboardCommand(SystemManager& m);
    void execute() override;
};

