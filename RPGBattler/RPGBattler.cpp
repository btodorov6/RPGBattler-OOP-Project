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

    User player1("Borko", "pass1");
    User player2("Valyo", "pass2");


    BattleManager::getBattleManager().startBattle(player1, player2, *player1.getHero(0), *player2.getHero(0));
}