#ifndef GAMEHANDLER_H
#define GAMEHAMDLER_H
#include "coord.h"
#include "ship.h"
#include "admiral.h"
#include "gameVars.h"

class GameHandler{
public:
    void display_grid(Admirals) const;
    void clear_grid(Admirals);
    int set_ship(Admirals, ShipType, XY (&xy)[2]);
    int move_ship(Admirals, XY (&xy)[2]);
    int action_ship(Admirals, XY (&xy)[2]);
private:
    int turn = 0;
    Admiral admiral[2];
    bool check_c_oob(XY &); //out of bounds
    bool check_c_allign(XY &, XY &); // allineamento 
    bool is_free_space(XY &, XY &);
};

#endif