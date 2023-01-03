#ifndef BOT_H
#define BOT_H
#include "player.h"

class Bot : public Player{
public:
    Bot(GameHandler*);
    int get_ship_pos(char *) override;
    int get_ship_act(char *) override;
    // ovviamente le gen va sepre a buon fine, return sempre = 0;
private: 
    GameHandler* gh;
    void gen_rand_coord(XY (&xy)[2]) const;
    void gen_rand_ship_coord(XY (&xy)[2]) const;
    // variabili tipo difficolta' in caso di ia non comp. randomica
};

#endif