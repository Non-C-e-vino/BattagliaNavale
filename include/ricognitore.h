/*
 * 
 * @author Salese Alberto
 * 
 */

#ifndef RICOGNITORE_H
#define RICOGNITORE_H
#include "ship.h"
class Ricognitore : public Ship{
public:
    Ricognitore(const Ricognitore&) = delete;
    Ricognitore(XY *);
    Ricognitore operator=(const Ricognitore&) = delete;
    ShipAction get_action() const override{ return ShipAction::MoveAndSearch; }
    bool full_heal(); 
    bool heal();  
    bool is_core(Hull *) const override;
    Hull* get_hull(int x) override { return &hull[x]; }
    int get_size() const override { return size; }

private:
    static int constexpr size = 1;
    Hull hull[size];
};

#endif