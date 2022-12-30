#include "admiral.h"

void Admiral::add_ship(std::unique_ptr<Ship> &ship){
    if(shipLc == SHIPSN/2) return;
    ships[shipLc++] = ship.release();
    return;
}