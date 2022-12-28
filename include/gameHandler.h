#ifndef GAMEHANDLER_H
#define GAMEHAMDLER_H
#include <memory>
#include "admiral.h"
#include "gameVars.h"

class GameHandler{
public:
    void display_grid(Admirals) const;
    void clear_att_grid(Admirals);
    int set_ship(Admirals, ShipType, XY (&xy)[2]);
    int move_ship(Admirals, XY (&xy)[2]);
    int ship_action(Admirals, XY (&xy)[2]);
private:
    int turn = 0;
    Admiral admiral[2];
    bool check_c_oob(XY &) const; //out of bounds
    bool is_free_space(XY &) const;
    int gen_ship_c(XY *, XY (&xy)[2], int ) const;
    void set_ship_on_map(std::unique_ptr<Ship> &);
    void detach_ship_from_map(std::unique_ptr<Ship> &);
    bool action_fire(XY &);
    bool action_move_heal(XY &);
    bool action_move_search(XY &);
};

#endif