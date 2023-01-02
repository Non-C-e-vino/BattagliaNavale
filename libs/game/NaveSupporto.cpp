#include "naveSupporto.h"
#include <iostream>


NaveSupporto::NaveSupporto(XY * xy) {
    hp = size;
    for(int i = 0; i < size; ++i)
        hull[i] = Hull{this, xy[i]};
}

bool NaveSupporto::is_core(Hull* ref) const{
    if(hull[size/2].get_c() == ref->get_c()) return true;
    return false;
}

bool NaveSupporto::full_heal(){
    if(hp == size) return false;
    hull[0].heal();
    return true;
}

bool NaveSupporto::heal(){
    if(hp == size) return false;
    ++hp;
    return true;
}