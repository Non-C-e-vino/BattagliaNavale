#ifndef RICOGNITORE_H
#define RICOGNITORE_H
#include "ship.h"
class Ricognitore : public Ship{
public:
    Ricognitore(XY *);
    Action get_action() const override{ return Action::MoveAndSearch; }
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