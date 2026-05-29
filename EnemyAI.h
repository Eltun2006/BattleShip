#pragma once

#include "Grid.h"
#include "Ship.h"

class EnemyAI
{
public:
    EnemyAI();
    void attack(Grid& playerGrid, Ship* playerShips, int& over, bool& yourTurn);
};
