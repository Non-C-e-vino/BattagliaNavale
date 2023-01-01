#ifndef SHIP_H
#define SHIP_H
#include "coord.h"

enum class Action{Fire, MoveAndRepair, MoveAndSearch};
enum class ShipType{Cor, NDS, Sot};

struct Hull;

class Ship{
public:
    virtual Action get_action() const = 0;
    bool set_damage();
    virtual bool full_heal() = 0; 
    virtual bool heal() = 0;
    virtual bool is_core(Hull *) const = 0;
    virtual Hull* get_hull(int x) = 0; 
    virtual int get_size() const = 0; 
    bool is_sunk(){ return !hp; }
protected:
    int hp;
};

struct Hull{
public:
    Hull(){}
    Hull(Ship* owner, XY& c) : owner{owner}, c{c}{}
    Ship * getOwner(){ return owner; }
    bool is_hit() const { return !armor; }
    bool set_hit();
    XY get_c() const { return c; }
    void set_c(XY &c){ this->c = c; }
    bool heal();

private:
    XY c; 
    bool armor = true;
    Ship * owner; 
};

#endif