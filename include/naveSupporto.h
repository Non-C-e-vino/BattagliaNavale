/*
 * 
 * @author Salese Alberto
 * 
 */

#ifndef NAVE_SUPPORTO_H
#define NAVE_SUPPORTO_H
#include "ship.h"
class NaveSupporto : public Ship{
public:
    NaveSupporto(const NaveSupporto&) = delete;
    NaveSupporto(XY *);
    NaveSupporto operator=(const NaveSupporto&) = delete;
    ShipAction get_action() const override{ return ShipAction::MoveAndRepair; }
    bool full_heal(); 
    bool heal();  
    bool is_core(Hull *) const override;
    Hull* get_hull(int x) override { return &hull[x]; }
    int get_size() const override { return size; }

private:
    static int constexpr size = 3;
    Hull hull[size];
};

#endif