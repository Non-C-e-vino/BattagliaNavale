#include "ricognitore.h"

Ricognitore::Ricognitore(XY * xy) {
    hp = size;
    hull[0] = Hull{this, xy[0]};
}

bool Ricognitore::is_core(Hull* ref) const{
    if(hull[0].get_c() == ref->get_c()) return true;
    return false;
}

bool Ricognitore::full_heal(){
    if(hp == size) return false;
    hull[0].heal();
    return true;
}

bool Ricognitore::heal(){
    if(hp == size) return false;
    ++hp;
    return true;
}