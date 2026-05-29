#pragma once

#include "Ship.h"
#include "Grid.h"

void autoArrange(Ship* ships, Grid& grid, int plus);
bool placeShipHorizontal(Ship& ship, Grid& grid, int x, int y, int shipIndex);
bool placeShipVertical(Ship& ship, Grid& grid, int x, int y, int shipIndex);
