#pragma once
#include "Command.h"

class SystemManager;

class LoginCommand : public Command
{
private:
    SystemManager& manager;
public:
    LoginCommand(SystemManager& m);
    void execute() override;
};