/**
 * 
 * @author Callegaro Gabriele
 * 
 */

#ifndef ADMIRAL_H
#define ADMIRAL_H
#include <memory>
#include "corazzata.h"
#include "naveSupporto.h"
#include "ricognitore.h"
#include "gameVars.h"


enum Admirals{ RedAdm, BlueAdm };

/**
 * @brief struttura dati utilizzata da GameHandler
 * 
 */
struct Admiral{
    Admiral(void){};

    //si potrebbero implementare assieme a move ass. e const. ma non avrebbero reale utilizzo
    Admiral(const Admiral&) = delete;
    Admiral operator=(const Admiral&) = delete; //non dovrebbe essere necessario con C++ 11
    Hull *defGrid[GRIDSIZE][GRIDSIZE]{};
    char attGrid[GRIDSIZE][GRIDSIZE]{};
    Ship *ships[SHIPS_TOT/2]{};
    int shipC = 0;
    void delete_ship(Ship*);

    /**
     * @brief Si appropria della nave passata e rilascia il puntatore di ship
     * se ha ancora slot liberi, altrimenti non fa nulla.
     * 
     * @param ship La nave di cui l'ammiraglio deve impadronirsi.
     */
    void add_ship(std::unique_ptr<Ship>& ship);
    ~Admiral();
};
    

#endif