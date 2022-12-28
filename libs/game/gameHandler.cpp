#include "gameHandler.h"
#include <iostream>


int GameHandler::set_ship(Admirals adm, ShipType st, XY (&xy)[2]){
    if(check_c_oob(xy[0]) || check_c_oob(xy[1]))
        return -1;

    XY shipC[5];
    if(int err = gen_ship_c(shipC, xy, (int)st*2+1))
        return err -10;

    std::unique_ptr<Ship> ship; 
    
    switch((int)st){
        case 2:
            ship = std::make_unique<Corazzata>(shipC);
            break;
        case 1:
        case 0:
        default:
            return -2;
    }

    set_ship_on_map(ship);

    admiral[(int)adm].add_ship(ship);

    if(ship.get() != nullptr)    //admiral non ha accettato il punattore (es. ah già 8 navi)
        return -3;
    
    return 0;
}
void GameHandler::display_grid(Admirals adm) const{
    //...
    return;
}

bool GameHandler::check_c_oob(XY &c) const {
    //...
    return false;
}

bool GameHandler::is_free_space(XY &) const {
    //...
    return true;
}

int GameHandler::gen_ship_c(XY *, XY (&xy)[2], int) const {
    //...
    //da due coord. restituisce un array di coordinate contigne (dove sarà la barca)
    //utile in fase di creazione e di spostamento
    //controlla: is free space, is alligned, in ship-coherent.
    return 0;
}

void GameHandler::detach_ship_from_map(std::unique_ptr<Ship> &ship){
    //setta le caselle della griglia che al momento puntano allo scafo di ship a nullptr (movimento e distruzione) 
}
void GameHandler::set_ship_on_map(std::unique_ptr<Ship> &ship){
    //fa si che le corrette caselle della gliglia di difesa puntino ai relativi scafi che le occupano  (movimento e creazione)
}


