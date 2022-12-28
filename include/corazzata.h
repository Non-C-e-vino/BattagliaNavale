#ifndef CORAZZATA_H
#define CORAZZATA_H
#include "ship.h"
class Corazzata : public Ship{
public:
    Corazzata(XY *);
    Action action() const override{ return Action::Fire; }
    bool is_hit(XY &) const override;    //inutile?
    bool is_core(Hull &) const override;
    bool set_damage(XY &) override;      //inutile?
    Hull & get_hull(int x) override { return hull[x]; }

private:
    static int constexpr size = 5;
    Hull hull[size];
};

#endif