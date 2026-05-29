#pragma once

class Ship
{
public:
    int deck;
    bool horizontal;
    bool alive;
    int x;
    int y;

    Ship();
    void load(int deckCount);
};

void loadAllShips(Ship* ships, int count);
