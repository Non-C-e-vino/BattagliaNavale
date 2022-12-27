#ifndef PLAYER_H
#define PLAYER_H
#include "coord.h"


class Player{
public:
    virtual int get_input(char *) = 0;  //forse (&char)[6] meglio? piu' leggibile
    //legge coordinate, usa coord_convert()
};

#endif