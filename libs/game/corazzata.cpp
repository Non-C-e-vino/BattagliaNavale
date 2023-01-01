#include "corazzata.h"

Corazzata::Corazzata(XY * xy) {
    hp = size;
    for(int i = 0; i < size; ++i)
        hull[i] = Hull{this, xy[i]};
}

bool Corazzata::is_core(Hull* ref) const{
    if(hull[size/2].get_c() == ref->get_c()) return true;
    return false;
}

bool Corazzata::full_heal(){
    if(hp == size) return false;
    for(int i = 0; i < size; ++i)
        hull[i].heal();
    return true;
}

bool Corazzata::heal(){
    if(hp == size) return false;
    ++hp;
    return true;
}