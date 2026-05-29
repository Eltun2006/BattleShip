#include "Placement.h"
#include <cstdlib>

bool placeShipHorizontal(Ship& ship, Grid& grid, int x, int y, int shipIndex)
{
    if (grid.getCell(y - 1, x) != 0 || grid.getCell(y - 1, x + ship.deck * 2 - 2) != 0)
        return false;

    ship.x = x + 2;
    ship.y = y;

    for (int q = 0; q < 3; q++)
        for (int w = 1; w < ship.deck * 3 + 1; w++)
            grid.setCell(y - 2 + q, x - 3 + w, 1);

    for (int g = 0; g < 2 * ship.deck; g++)
        grid.setCell(y - 1, x + g, 13 - shipIndex);

    return true;
}

bool placeShipVertical(Ship& ship, Grid& grid, int x, int y, int shipIndex)
{
    if (grid.getCell(y - 1, x) != 0 || grid.getCell(y + ship.deck - 2, x) != 0)
        return false;

    ship.x = x + 2;
    ship.y = y;

    for (int q = 0; q < ship.deck + 2; q++)
        for (int w = 0; w < 6; w++)
            grid.setCell(y - 2 + q, x - 2 + w, 1);

    for (int g = 0; g < ship.deck; g++)
        for (int n = 0; n < 2; n++)
            grid.setCell(y - 1 + g, x + n, 13 - shipIndex);

    return true;
}

void autoArrange(Ship* ships, Grid& grid, int plus)
{
    int ship = plus;

    while (ship < plus + 10)
    {
        ships[ship].horizontal = rand() % 2;
        int y = 2 + rand() % 9;
        int x = (1 + rand() % 9) * 2;

        if (!ships[ship].horizontal && y + ships[ship].deck >= 13)
            y -= y + ships[ship].deck - 12;

        if (ships[ship].horizontal && x + ships[ship].deck * 2 >= 24)
            x -= (x + ships[ship].deck * 2) - 22;

        if (ships[ship].horizontal)
        {
            if (placeShipHorizontal(ships[ship], grid, x, y, ship - plus))
                ship++;
        }
        else
        {
            if (placeShipVertical(ships[ship], grid, x, y, ship - plus))
                ship++;
        }
    }
}
