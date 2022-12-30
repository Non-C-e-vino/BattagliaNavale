#ifndef SHIP_H
#define SHIP_H
#include "coord.h"

enum class Action{Fire, MoveAndRepair, MoveAndSearch};
enum class ShipType{Cor, NDS, Sot};

struct Hull;

class Ship{
public:
    virtual Action action() const = 0;
    virtual bool is_hit(XY &) const = 0; //prob inutile
    bool set_damage(); //non serve, ma non capisco perche' non si possa definire virtual
    virtual bool is_core(Hull &) const = 0;
    virtual Hull & get_hull(int x) = 0; 
    virtual int get_size() const = 0; 
    bool is_sunk(){ return !hp; }
protected:
    int hp;
};

struct Hull{
public:
    Hull(){}
    Hull(Ship* owner, XY& c) : owner{owner}, c{c}, armor{true}{}
    Ship * getOwner(){ return owner; }
    bool is_hit() const { return armor; }
    void set_hit(){ armor = false; }    //si potrebbero aggiungere controlli
    void heal(){ armor = true; }
    XY get_c() const { return c; }
    void set_c(XY &c){ this->c = c; }

private:
    XY c; 
    bool armor;
    Ship * owner; 
};

#endif