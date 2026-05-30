#pragma once

#include "Grid.h"
#include "Ship.h"
#include "EnemyAI.h"

class Game
{
public:
    Game();
    void run();

private:
    Grid playerGrid;
    Grid enemyGrid;
    Ship ships[20];
    EnemyAI ai;
    bool yourTurn;
    int over;
    int cursorX;
    int cursorY;

    void drawBothFields();
    void showMenu(int num);
    void paintVariantMenu(char variant[2][30], int selected);
    void setupManual();
    void setupAuto();
    void playerAttack();
    void enemyAttack();
};
