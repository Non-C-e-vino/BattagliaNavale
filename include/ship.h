#ifndef SHIP_H
#define SHIP_H
#include "coord.h"
//potrebbe essere interna ma difficile
enum Action{Fire, MoveAndRepair, MoveAndSearch};

class Ship{
public:
    virtual void action() = 0;
    Coord isHit();  // GROSSO PROBLEMA: non posso cercare tra tutte le coordinate di tutte le navi
                    // per tutte le caselle di move e repair tutte le volte. Forse urge STL?
private:
    struct Hull{ Coord c; bool armor; };
};

#endif