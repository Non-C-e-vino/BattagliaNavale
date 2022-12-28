#ifndef SHIP_H
#define SHIP_H
#include "coord.h"
//potrebbe essere interna ma difficile
enum Action{Fire, MoveAndRepair, MoveAndSearch};
enum ShipType{Cor, NDS, Sot};

struct Hull{ 
    XY c; 
    bool armor; 
};

class Ship{
public:
    virtual void action() const = 0;
    virtual bool isHit(XY) const = 0;
    virtual bool isCore(/**/) const = 0;
    bool isSunk(){ return !hp; }
                    // GROSSO PROBLEMA: non posso cercare tra tutte le coordinate di tutte le navi
                    // per tutte le caselle di move e repair tutte le volte. Forse urge STL?
private:
    int hp;
};

#endif