#include "gameHandler.h"
#include <iostream>

int GameHandler::set_ship(Admirals adm, ShipType st, XY (&xy)[2]){
    if(check_c_oob(xy[0]) || check_c_oob(xy[1]))
        return -1;
    if(!check_c_allign(xy[0], xy[1]))
        return -2;
    if(!is_free_space(xy[0], xy[1]))
        return -3;
    switch((int)st){
        case 2: std::cout << "corazzata-test\n";
            //Admirals[(int)adm].ships
            break;
        default: return -4;
    }
    
    return 0;
}

bool GameHandler::check_c_oob(XY &c){
    //...
    return false;
}
bool GameHandler::check_c_allign(XY &c1, XY &c2){
    //...
    return true;
} 
bool GameHandler::is_free_space(XY &c1, XY &c2){
    //...
    return true;
} 

