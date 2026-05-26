#include <iostream>
#include <ctime>
#include "BattleManager.h"
#include "User.h"
#include "Hero.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
#include "SystemManager.h"
int main()
{
    srand(time(NULL));

    SystemManager::getSystemManager().run();
}