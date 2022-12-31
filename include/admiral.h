#ifndef ADMIRAL_H
#define ADMIRAL_H
#include <memory>
#include "corazzata.h"
#include "gameVars.h"


enum Admirals{ RedAdm, BlueAdm };

struct Admiral{
    Hull *defGrid[GRIDSIZE][GRIDSIZE];
    char attGrid[GRIDSIZE][GRIDSIZE];
    Ship *ships[SHIPSN/2];
    int shipLc = 0;
    //ipoteticamente ci sono 3 opzioni per i data memb:
    //  meno flessibile: 3 array per 3 tipi di navi
    //  medio flessibile: array di puntatori a generiche navi <-----------
    //  flessibile (?troppo): vettore di puntatori a generiche navi
    void add_ship(std::unique_ptr<Ship>&);
    //MANCA IL DISTRUTTORE
};

#endif