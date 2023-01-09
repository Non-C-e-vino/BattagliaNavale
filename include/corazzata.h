#ifndef CORAZZATA_H
#define CORAZZATA_H
#include "ship.h"
class Corazzata : public Ship{
public:
    Corazzata(const Corazzata&) = delete;
    Corazzata(XY *);
    Corazzata operator=(const Corazzata&) = delete;
    ShipAction get_action() const override{ return ShipAction::Fire; }
    bool full_heal(); 
    bool heal(); 
    bool is_core(Hull *) const override; //possibilmente helper f 
    Hull* get_hull(int x) override { return &hull[x]; }
    int get_size() const override { return size; }

private:
    static int constexpr size = 5;
    Hull hull[size];
};

#endif