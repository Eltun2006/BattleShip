#include "EnemyAI.h"
#include "ConsoleUtils.h"
#include <cstdlib>
#include <windows.h>

EnemyAI::EnemyAI()
{
}

void EnemyAI::attack(Grid& playerGrid, Ship* playerShips, int& over, bool& yourTurn)
{
    Sleep(rand() % 400);

    int x = (2 + rand() % 10) * 2;
    int y = 2 + rand() % 10;

    if (playerGrid.getCell(y - 1, x - 1) >= 4)
    {
        for (int i = 0; i < 2; i++)
            playerGrid.setCell(y - 1, x - 2 + i, 3);

        playerGrid.checkExplosion(playerShips, 0, over);
    }
    else if (playerGrid.getCell(y - 1, x - 1) <= 2)
    {
        for (int i = 0; i < 2; i++)
            playerGrid.setCell(y - 1, x - 2 + i, 2);

        yourTurn = true;
    }
}
