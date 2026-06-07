#pragma once
#include "Command.h"

class SystemManager;

class LogoutCommand : public Command
{
private:
    SystemManager& manager;
public:
    LogoutCommand(SystemManager& m);
    void execute() override;
};