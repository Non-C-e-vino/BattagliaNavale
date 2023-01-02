#ifndef ADMIRAL_H
#define ADMIRAL_H
#include <memory>
#include "corazzata.h"
#include "naveSupporto.h"
#include "ricognitore.h"
#include "gameVars.h"


enum Admirals{ RedAdm, BlueAdm };

struct Admiral{
    Admiral(void){};
    Admiral(const Admiral&) = delete;
    Admiral operator=(const Admiral&) = delete; //non dovrebbe essere necessario con C++ 11
    Hull *defGrid[GRIDSIZE][GRIDSIZE];
    char attGrid[GRIDSIZE][GRIDSIZE];
    Ship *ships[SHIPSN/2];
    int shipC = 0;
    //ipoteticamente ci sono 3 opzioni per i data memb:
    //  meno flessibile: 3 array per 3 tipi di navi
    //  medio flessibile: array di puntatori a generiche navi <-----------
    //  flessibile (?troppo): vettore di puntatori a generiche navi
    void delete_ship(Ship*);
    void add_ship(std::unique_ptr<Ship>&);
    ~Admiral();
};
    

#endif