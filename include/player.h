#ifndef PLAYER_H
#define PLAYER_H
#include "coord.h"
#include "gameHandler.h"

class Player{
public:
    virtual int get_ship_pos(char *) = 0;
    virtual int get_ship_act(char *) = 0;
    //forse (&char)[6] meglio? piu' leggibile
};

#endif