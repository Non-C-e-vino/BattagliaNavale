#ifndef PLAYER_H
#define PLAYER_H
#include "coord.h"


class Player{
public:
    virtual Coord getInput() = 0;
    //legge coordinate, usa coordCnvert
};

#endif