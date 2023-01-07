#include "bot.h"
#include "gameVars.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

Bot::Bot(GameHandler* gh) : gh (gh){}

int Bot::get_ship_pos(char *inp)
{
    XY xy[2];
    gen_rand_ship_coord(xy);
    coord_to_char(xy, inp);
    std::cout << "Bot input." << std::endl;
    return 0;
}

int Bot::get_ship_act(char *inp)
{
    XY xy[2];
    gen_rand_coord(xy);
    coord_to_char(xy, inp);
    std::cout << "Bot input." << std::endl;
    return 0;
}

void Bot::gen_rand_ship_coord(XY (&xy)[2]) const 
{
    xy[0].xy[0] = rand() % GRIDSIZE;
    xy[0].xy[1] = rand() % GRIDSIZE;
    xy[1] = xy[0];

    int dim = rand()%2;     //orientamento della nave, asse x o y
    int type;               //tipo nave

    if(gh->get_turn() < CORA) type = 2;
    else if(gh->get_turn() < SUPP + CORA) type = 1;
    else if(gh->get_turn() < SHIPSN) type = 0;

    xy[1].xy[dim] += type*2; 
    if(check_c_oob(xy[1])) xy[1].xy[dim] -= type*4; 

    //std::cout << "\n" << xy[0].xy[0] << ' '  << xy[0].xy[1] << ' '  << xy[1].xy[0] << ' '  << xy[1].xy[1] << ' ' << gh->get_turn() << '\n';
}
void Bot::gen_rand_coord(XY (&xy)[2]) const 
{
    if(Admirals((gh->get_turn() + gh->get_coin())%2) == RedAdm)
        xy[0] = gh->get_core(rand()%gh->get_active_ships_n(RedAdm))->get_c();
    else
        xy[0] = gh->get_core(gh->get_active_ships_n(RedAdm) + rand()%gh->get_active_ships_n(BlueAdm))->get_c();
    xy[1].xy[0] = rand() % GRIDSIZE;
    xy[1].xy[1] = rand() % GRIDSIZE;
}