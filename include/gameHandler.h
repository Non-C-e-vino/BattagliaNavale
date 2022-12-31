#ifndef GAMEHANDLER_H
#define GAMEHAMDLER_H
#include <memory>
#include <vector>
#include "admiral.h"
#include "gameVars.h"

class GameHandler{
public:
    void display_grids(Admirals) const;
    void clear_att_grid(Admirals);
    void clear_miss_sonar(Admirals);
    int set_ship(Admirals, ShipType, XY (&xy)[2]);
    int ship_action(Admirals, XY (&xy)[2]);
    Hull* get_core(int);
    void set_cores();
    bool next_turn();
    int get_turn(){ return turn; }
    void throw_coin();
    int get_coin(){ return (int)coin; }
private:
    int turn = 0;
    bool coin;
    Admiral admiral[2];
    std::vector<Hull*> cores;
    int gen_ship_c(XY *, XY (&xy)[2], int, Admirals) const;
    void set_ship_on_map(std::unique_ptr<Ship> &, Admirals);
    void detach_ship_from_map(std::unique_ptr<Ship> &);
    int action_fire(XY&, Admirals);
    int action_move_heal(Hull* h, XY& xy, Admirals adm);
    int action_move_search(XY&, Admirals);
    bool move_ship(Hull* h, XY& xy, Admirals adm);
};

#endif