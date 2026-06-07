#include "ShopCommand.h"
#include "SystemManager.h"

ShopCommand::ShopCommand(SystemManager& m) : manager(m) {}

void ShopCommand::execute()
{
    manager.shopMenu();
}