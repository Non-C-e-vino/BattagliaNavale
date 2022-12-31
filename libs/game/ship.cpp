#include "ship.h"
#include "iostream"

bool Ship::set_damage(){
    if(hp == 0) return false;
    --hp;
    return true;
}

bool Hull::set_hit(){ 
    if (armor == false) return false;
    armor = false;
    if(!owner->set_damage()) throw std::logic_error("colpita nave già affondata");
    return true;
} 