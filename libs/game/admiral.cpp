#include "admiral.h"

void Admiral::add_ship(std::unique_ptr<Ship> &ship){
    ship.release();
    return;
}