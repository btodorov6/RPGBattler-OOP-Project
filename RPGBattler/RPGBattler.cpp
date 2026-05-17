#include <iostream>
#include <ctime>
#include "BattleManager.h"
#include "User.h"
#include "Hero.h"
#include "Warrior.h"
#include "Mage.h"
#include "Archer.h"
int main()
{
    srand(time(NULL));
    Warrior hero1Test("Borkos");
    Mage hero2Test("Valkos");
    BattleManager::getBattleManager().startBattle(hero1Test, hero2Test);
}