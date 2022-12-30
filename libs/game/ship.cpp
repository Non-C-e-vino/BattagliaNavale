#include "ship.h"

bool Ship::set_damage(){
    if(--hp < 0) return false;
    return true;
}