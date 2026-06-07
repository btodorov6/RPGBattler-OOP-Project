#pragma once
#include "Command.h"

class SystemManager;

class ExitCommand : public Command
{
private:
    SystemManager& manager;
public:
    ExitCommand(SystemManager& m);
    void execute() override;
};