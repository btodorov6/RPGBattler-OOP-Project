#pragma once
#include "Command.h"

class SystemManager;

class ShopCommand : public Command
{
private:
    SystemManager& manager;
public:
    ShopCommand(SystemManager& m);
    void execute() override;
};