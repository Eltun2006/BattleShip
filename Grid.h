#pragma once

#include "Ship.h"

class Grid
{
public:
    int cells[12][24];

    Grid();
    void reset();
    int getCell(int row, int col) const;
    void setCell(int row, int col, int val);
    void checkExplosion(Ship* ships, int plus, int& over);
};
