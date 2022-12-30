#ifndef PLAYER_H
#define PLAYER_H
#include "coord.h"


class Player{
public:
    virtual int get_ship_pos(char *) = 0;
    virtual int get_ship_act(char *) = 0;
private:
    virtual int get_input(char *) = 0;
    //forse (&char)[6] meglio? piu' leggibile
    //legge coordinate, usa coord_convert()
};

#endif