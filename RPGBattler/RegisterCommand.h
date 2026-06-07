#pragma once
#include "Command.h"

class SystemManager;

class RegisterCommand : public Command
{
private:
    SystemManager& manager;
public:
    RegisterCommand(SystemManager& m);
    void execute() override;
};