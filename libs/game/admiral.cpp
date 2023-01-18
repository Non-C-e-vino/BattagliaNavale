/**
 * 
 * @author Callegaro Gabriele
 * 
 */

#include "admiral.h"

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