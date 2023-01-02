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
    bool game_end(Admirals adm);
    int get_turn(){ return turn; }
    void flip_coin();
    int get_coin(){ return (int)coin; }
    int get_active_ships_n(Admirals adm){ return admiral[(int)adm].shipC; }
    void remove_all_sunk(Admirals);
private:
    int turn = 0;
    bool coin;
    Admiral admiral[2];
    std::vector<Hull*> cores;
    int gen_ship_c(XY *, XY (&xy)[2], int, Admirals) const;
    void set_ship_on_map(std::unique_ptr<Ship>& , Admirals);
    void set_ship_on_map(Ship*, Admirals);
    void detach_ship_from_map(Ship*, Admirals);
    int action_fire(XY&, Admirals);
    int action_move_heal(Hull*, XY&, Admirals);
    int action_move_search(Hull*, XY&, Admirals);
    bool move_ship(Hull*, XY&, Admirals);
    void heal_aoe(Hull*, Admirals);
    void ricognizione(XY&, Admirals);
};

//TODO: migliorare turn counter, 

#endif