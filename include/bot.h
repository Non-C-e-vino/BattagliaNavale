#ifndef BOT_H
#define BOT_H
#include "player.h"
#include <iostream>

class Bot : public Player{
public:
    Coord get_input() override;
private: 
    // variabili tipo difficolta' in caso di ia non comp. randomica
    Coord gen_rand_coord();
};

#endif