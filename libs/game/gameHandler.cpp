#include "gameHandler.h"
#include <iostream>


int GameHandler::set_ship(Admirals adm, ShipType st, XY (&xy)[2]){
    if(check_c_oob(xy[0]) || check_c_oob(xy[1]))
        return -1;

    XY shipC[5];
    if(int err = gen_ship_c(shipC, xy, (int)st*2+1, adm))
        return err -10;

    std::unique_ptr<Ship> ship; 
    
    switch((int)st){
        case 2:
            ship = std::make_unique<Corazzata>(shipC);
            break;
        case 1:
            ship = std::make_unique<NaveSupporto>(shipC);
            break;
        case 0:
            //manca implementazione nave
        default:
            return -2;
    }

    set_ship_on_map(ship, adm);

    admiral[(int)adm].add_ship(ship);

    if(ship.get() != nullptr)    //admiral non ha accettato il punattore (es. ha gia' 8 navi)
        return -3;
    
    return 0;
}

int GameHandler::ship_action(Admirals adm, XY (&xy)[2]){
    if(check_c_oob(xy[0])) return -1;
    Hull* h = admiral[(int)adm].defGrid[xy[0].xy[0]][xy[0].xy[1]];
    if(h->getOwner()->is_sunk()) return -2;
    if(h != nullptr && h->getOwner()->is_core(h))
        switch((int)(h->getOwner()->get_action())){
            case 0:
                if(int err = action_fire(xy[1], adm))
                    return err -10;
                break;
            case 1:
                if(int err = action_move_heal(h, xy[0], adm))
                    return err -10;
                break;
            case 2:
                if(int err = action_move_search(xy[1], adm))
                    return err -10;
                break;
            default: return -4;
        }
    else return -3;
    return 0;
}

int GameHandler::action_fire(XY& xy, Admirals adm){
    if(check_c_oob(xy)) return -1;
    Admirals enemy(Admirals(((int)adm+1)%2));
    Hull* h = admiral[(int)enemy].defGrid[xy.xy[0]][xy.xy[1]];
    if(h != nullptr){
        h->set_hit();
        //destroy ship & remove from cores if sunk
        admiral[(int)adm].attGrid[xy.xy[0]][xy.xy[1]] = 'X';
    }else admiral[(int)adm].attGrid[xy.xy[0]][xy.xy[1]] = 'O';

    return 0;
}

int GameHandler::action_move_heal(Hull* h, XY& xy, Admirals adm){
    if(check_c_oob(xy)) return -1;
    if(move_ship(h, xy, adm)){
        //heal
        std::cout << "HEAL\n";
    }else return -2;
    return 0;
}

int GameHandler::action_move_search(XY& xy, Admirals adm){
    if(check_c_oob(xy)) return -1;

    return -1;
}

bool GameHandler::move_ship(Hull* h, XY& xy, Admirals adm){

    return true;
}

void GameHandler::display_grids(Admirals adm) const {
    std::cout << "\t----GRIGLIA DI DIFESA----\t----GRIGLIA D'ATTACCO----\n" << std::endl;
    std::cout << "\t";

    for(int c = 0; c < GRIDSIZE; ++c) std::cout << ' ' <<  (c+1)%10;
    std::cout << "\t";
    for(int c = 0; c < GRIDSIZE; ++c) std::cout << ' ' <<  (c+1)%10;

    std::cout << "\n";
    for(int i = 0; i < GRIDSIZE; ++i){
        std::cout << (char)('A' + i);
        std::cout << "\t";
        for(int c = 0; c < GRIDSIZE; ++c){
            if (admiral[(int)adm].defGrid[i][c] == nullptr) std::cout << " ~";
            else switch(admiral[(int)adm].defGrid[i][c]->getOwner()->get_size()){
                case 5: 
                    if(admiral[(int)adm].defGrid[i][c]->is_hit()) std::cout << " @";
                    else std::cout << " C";
                    break;
                case 3:
                    if(admiral[(int)adm].defGrid[i][c]->is_hit()) std::cout << " $";
                    else std::cout << " S";
                    break;
                case 1:
                    if(admiral[(int)adm].defGrid[i][c]->is_hit()) std::cout << " £";
                    else std::cout << " E";
                    break;
            }
        }
        std::cout << "\t";
        for(int c = 0; c < GRIDSIZE; ++c){
            if (admiral[(int)adm].attGrid[i][c] == 0) std::cout << " ~";
            else std::cout << ' ' << admiral[(int)adm].attGrid[i][c];
        }
        std::cout << "\n";
    }
    return;
}

void GameHandler::clear_att_grid(Admirals adm){
    //...
    return;
}

void GameHandler::clear_miss_sonar(Admirals adm){
    //...
    return;
}

int GameHandler::gen_ship_c(XY *shipC, XY (&xy)[2], int size, Admirals adm) const {
    //da due coord. restituisce un array di coordinate contigne (dove sarà la barca)
    //utile in fase di creazione e di spostamento
    //controlla: is free space, is alligned, in ship-coherent. (-1, -2, -3)

    int sign = -1;
    int dim = 1;
    if(xy[0].xy[0]==xy[1].xy[0])
        if(xy[0].xy[1]<=xy[1].xy[1]) sign = 0;
        else sign = 1;
    if(xy[0].xy[1]==xy[1].xy[1]){
        dim = 0;
        if(xy[0].xy[0]<=xy[1].xy[0]) sign = 0;
        else sign = 1;
    }
    if(sign == -1) return -1;

    XY c = xy[0];
    for(int i = 0; i < size; i++){
        if(admiral[(int)adm].defGrid[c.xy[0]][c.xy[1]] != nullptr) return -2;
        shipC[i] = c;
        //std::cout << "\n" << c.xy[0] << ' ' << "\n" << c.xy[1] << '\n';
        if(sign) --c.xy[dim];
        else ++c.xy[dim];
    }

    if(shipC[size-1] != xy[1]) return -3;
    
    return 0;
}

void GameHandler::set_ship_on_map(std::unique_ptr<Ship> &ship, Admirals adm){
    //fa si che le corrette caselle della gliglia di difesa puntino ai relativi scafi che le occupano  (movimento e creazione)
    for(int i = 0; i < ship->get_size(); i++){
        XY c = ship->get_hull(i)->get_c();
        admiral[(int)adm].defGrid[c.xy[0]][c.xy[1]] = ship->get_hull(i);
    }
}

void GameHandler::detach_ship_from_map(std::unique_ptr<Ship> &ship){
    //setta le caselle della griglia che al momento puntano allo scafo di ship a nullptr (movimento e distruzione) 
}

void GameHandler::set_cores(){
    for(int i = 0; i < 2; ++i)
        for(int c = 0; c < SHIPSN/2; ++c)
            if(admiral[i].ships[c] != nullptr) cores.push_back(admiral[i].ships[c]->get_hull(admiral[i].ships[c]->get_size()/2));
}

Hull* GameHandler::get_core(int i){
    return cores.at(i);
}

bool GameHandler::next_turn() {
    if(turn > MAXTURNS) return false; 
    ++turn;
    return true; 
}

void GameHandler::throw_coin() {
    coin = rand()%2; 
    return; 
}