#include "Ship.h"

Ship::Ship()
{
    deck = 0;
    horizontal = true;
    alive = true;
    x = 0;
    y = 0;
}

void Ship::load(int deckCount)
{
    deck = deckCount;
}

void loadAllShips(Ship* ships, int count)
{
    for (int i = 0; i < count; i++)
    {
        int offset = i % 10;

        if (offset == 0)
            ships[i].load(4);
        else if (offset >= 1 && offset <= 2)
            ships[i].load(3);
        else if (offset >= 3 && offset <= 5)
            ships[i].load(2);
        else
            ships[i].load(1);
    }
}
