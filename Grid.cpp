#include "Grid.h"
#include <cstring>

Grid::Grid()
{
    reset();
}

void Grid::reset()
{
    memset(cells, 0, sizeof(cells));
}

int Grid::getCell(int row, int col) const
{
    return cells[row][col];
}

void Grid::setCell(int row, int col, int val)
{
    cells[row][col] = val;
}

void Grid::checkExplosion(Ship* ships, int plus, int& over)
{
    int sunkCount = 0;
    bool alive = false;

    for (int n = 13; n > 3; n--)
    {
        alive = false;
        for (int i = 1; i < 11; i++)
        {
            for (int r = 2; r < 22; r++)
            {
                if (cells[i][r] == n)
                {
                    alive = true;
                    i = 11;
                    break;
                }
            }
        }

        if (!alive)
            ships[13 - n + plus].alive = false;
    }

    int A = 0;
    for (int i = plus; i < 10 + plus; i++)
    {
        int offset = i % 10;

        if (offset == 0)
            A = 0;
        else if (offset == 1 || offset == 2)
            A = 1;
        else if (offset >= 3 && offset <= 5)
            A = 2;
        else
            A = 3;

        if (!ships[i].alive)
        {
            if (ships[i].horizontal)
            {
                for (int q = 0; q < 3; q++)
                    for (int w = 0; w < ships[i].deck * 3 + A; w++)
                        cells[ships[i].y - 2 + q][ships[i].x - 4 + w] = 2;

                for (int g = 0; g < 2 * ships[i].deck; g++)
                    cells[ships[i].y - 1][ships[i].x - 2 + g] = 3;
            }
            else
            {
                for (int q = 0; q < ships[i].deck + 2; q++)
                    for (int w = -4; w < 2; w++)
                        cells[ships[i].y - 2 + q][ships[i].x + w] = 2;

                for (int g = 0; g < ships[i].deck; g++)
                    for (int n = -2; n < 0; n++)
                        cells[ships[i].y - 1 + g][ships[i].x + n] = 3;
            }
            sunkCount++;
        }
    }

    if (sunkCount == 10 && plus == 0)
        over = 1;
    else if (sunkCount == 10 && plus == 10)
        over = 2;
}
