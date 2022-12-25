#ifndef PLAYER_H
#define PLAYER_H
#include "coord.h"


class Player{
public:
    virtual Coord get_input() = 0;
    //legge coordinate, usa coord_convert()
};

#endif