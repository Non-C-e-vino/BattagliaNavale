#ifndef ADMIRAL_H
#define ADMIRAL_H
#include "ship.h"
#include "gameVars.h"

enum Admirals{ RedAdm, BlueAdm };

struct Admiral{
    Hull *DefGrid[MAPSIZE][MAPSIZE];
    char AttGrid[MAPSIZE][MAPSIZE];
    Ship *ships[SHIPSN/2];
    //ipoteticamente ci sono 3 opzioni per i data memb:
    //  meno flessibile: 3 array per 3 tipi di navi
    //  medio flessibile: array di puntatori a generiche navi <-----------
    //  flessibile (?troppo): vettore di puntatori a generiche navi
    
};

#endif