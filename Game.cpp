#include "Game.h"
#include "ConsoleUtils.h"
#include "Placement.h"
#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

Game::Game()
{
    yourTurn = rand() % 2;
    over = 0;
    cursorX = 37;
    cursorY = 2;

    loadAllShips(ships, 20);
}

void Game::showMenu(int num)
{
    char variant[11][40] = {
        "THE ENEMY THINKS WHERE TO STRIKE...",
        "THE ENEMY MISSED!",
        "ENEMY HIT!",
        "THE ENEMY HAS WON",
        "YOUR TURN",
        "YOU ARE MISSED",
        "YOU ARE HIT",
        "YOU WON! CONGRATULATIONS!\n\a",
        "+++++++++++++++++++++++++++++++++++++++",
        "YOU GOT IT, GO AGAIN!",
        "YOU ARE DESTROYED THE SHIP"
    };

    SetCursor(22, 15);
    setColor(Black, Black);
    for (int i = 0; i < 25; i++)
        cout << "                    ";

    SetCursor(22, 15);
    if (num > 0 && num < 4)
        setColor(Red, Black);
    else
        setColor(Green, Black);

    for (int i = 0; i < 30; i++)
        cout << variant[num][i];
}

void Game::paintVariantMenu(char variant[2][30], int selected)
{
    system("cls");
    for (int i = 0; i < 2; i++)
    {
        SetCursor(30, 6 + i);
        for (int j = 0; j < 30; j++)
        {
            if (i == selected)
                setColor(Black, White);
            else
                setColor(White, Black);
            cout << variant[i][j];
        }
    }
    CreatField(0, 9);
}

void Game::setupAuto()
{
    autoArrange(ships, playerGrid, 0);
    PaintPos(playerGrid.cells, 2, 0);
}

void Game::setupManual()
{
    int num = 0;
    int x = 2, y = 2;

    do
    {
        PaintPos(playerGrid.cells, 2, 0);
        SetCursor(x, y);
        setColor(Black, Black);

        if (ships[num].horizontal)
        {
            for (int i = 0; i < ships[num].deck; i++)
                cout << "  ";
        }
        else
        {
            y += ships[num].deck;
            for (int i = 0; i < ships[num].deck; i++)
            {
                cout << "  ";
                y--;
                SetCursor(x, y);
            }
        }

        int key = _getch();
        switch (key)
        {
        case Left:
            if (x > 3) x -= 2;
            break;
        case Right:
            if (ships[num].horizontal)
            { if (x < 22 - ships[num].deck * 2) x += 2; }
            else
            { if (x < 20) x += 2; }
            break;
        case Up:
            if (y > 2) y--;
            break;
        case Down:
            if (ships[num].horizontal)
            { if (y < 11) y++; }
            else
            { if (y < 12 - ships[num].deck) y++; }
            break;
        case R:
            ships[num].horizontal = !ships[num].horizontal;
            if (!ships[num].horizontal && y + ships[num].deck >= 13)
                y -= y + ships[num].deck - 12;
            else if (ships[num].horizontal && x + ships[num].deck * 2 >= 24)
                x -= (x + ships[num].deck * 2) - 22;
            break;
        case Enter:
            if (ships[num].horizontal)
            {
                if (placeShipHorizontal(ships[num], playerGrid, x, y, num))
                    num++;
            }
            else
            {
                if (placeShipVertical(ships[num], playerGrid, x, y, num))
                    num++;
            }
            break;
        }
    } while (num <= 9);
}

void Game::playerAttack()
{
    int key = 0;
    do
    {
        PaintPos(enemyGrid.cells, 37, 15);
        setColor(DarkGray, DarkGray);
        SetCursor(cursorX, cursorY);
        cout << "  ";

        key = _getch();
        switch (key)
        {
        case Left:  if (cursorX > 38) cursorX -= 2; break;
        case Right: if (cursorX < 55) cursorX += 2; break;
        case Up:    if (cursorY > 2)  cursorY--;     break;
        case Down:  if (cursorY < 11) cursorY++;     break;
        case Enter:
            if (enemyGrid.getCell(cursorY - 1, cursorX - 35) >= 4)
            {
                for (int i = 0; i < 2; i++)
                    enemyGrid.setCell(cursorY - 1, cursorX - 35 + i, 3);
                enemyGrid.checkExplosion(ships, 10, over);
                showMenu(9);
                Sleep(500);
            }
            else if (enemyGrid.getCell(cursorY - 1, cursorX - 35) < 2)
            {
                for (int i = 0; i < 2; i++)
                    enemyGrid.setCell(cursorY - 1, cursorX - 35 + i, 2);
                Sleep(500);
                showMenu(5);
                yourTurn = false;
            }
            break;
        }
    } while (key != Enter);
}

void Game::enemyAttack()
{
    showMenu(0);
    PaintPos(playerGrid.cells, 2, 0);
    ai.attack(playerGrid, ships, over, yourTurn);

    if (!yourTurn)
        showMenu(2);
    else
        showMenu(1);

    Sleep(rand() % 750);
}

void Game::run()
{
    char variant[2][30] = { "-->RANDOM<--", "-->MANUAL<--" };
    int key = 0, y = 1, change = 1, A = 0;

    theme();
    Sleep(1500);
    setColor(White, Black);
    system("cls");
    CreatField(0, 9);
    paintVariantMenu(variant, change);

    do
    {
        key = _getch();
        switch (key)
        {
        case Up:
            if (y > 0) { y--; change = y; paintVariantMenu(variant, change); }
            break;
        case Down:
            if (y < 1) { y++; change = y; paintVariantMenu(variant, change); }
            break;
        case Enter:
            if (change == 0) { setupAuto();   A++; }
            if (change == 1) { setupManual(); A++; }
            break;
        }
    } while (A < 1);

    Sleep(20);
    CreatField(35, 4);
    autoArrange(ships, enemyGrid, 10);
    PaintPos(enemyGrid.cells, 37, 15);

    do
    {
        if (yourTurn)
            playerAttack();
        else
            enemyAttack();
    } while (over == 0);

    PaintPos(playerGrid.cells, 2, 0);
    PaintPos(enemyGrid.cells, 37, 15);

    if (over == 2)
        showMenu(7);
    else
        showMenu(3);

    Sleep(500000);
}
