#include "admiral.h"

Admiral::Admiral()
{
    std::fill(&defGrid[0][0], &defGrid[0][0] + GRIDSIZE*GRIDSIZE, nullptr);
    std::fill(&attGrid[0][0], &attGrid[0][0] + GRIDSIZE*GRIDSIZE, (char)0);
}

void Admiral::add_ship(std::unique_ptr<Ship> &ship)
{
    if(shipC == SHIPS_TOT/2) return;
    ships[shipC++] = ship.release();
    return;
}

void Admiral::delete_ship(Ship* ship)
{
    for(int i = 0; i < SHIPS_TOT/2; ++i)
        if(ships[i] == ship)
        {
            delete ships[i];
            ships[i] = nullptr;
            --shipC;
            break;
        }
}

Admiral::~Admiral()
{
    for(int i = 0; i < SHIPS_TOT/2; ++i)
        if(ships[i] != nullptr)
        {
            delete ships[i];
            ships[i] = nullptr;
            --shipC;
        }
}