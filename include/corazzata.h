#ifndef CORAZZATA_H
#define CORAZZATA_H
#include "ship.h"
class Corazzata : public Ship{
public:
    Corazzata(XY *);
    Action get_action() const override{ return Action::Fire; }
    //bool is_hit(XY &) const override;
    bool is_core(Hull *) const override; //possibilmente helper f 
    Hull* get_hull(int x) override { return &hull[x]; }
    int get_size() const override { return size; }

private:
    static int constexpr size = 5;
    Hull hull[size];
};

#endif