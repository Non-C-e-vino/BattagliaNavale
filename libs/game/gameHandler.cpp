#include "gameHandler.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

int GameHandler::set_ship(Admirals adm, ShipType st, XY (&xy)[2])
{
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
            ship = std::make_unique<Ricognitore>(shipC);
            break;
        default:
            return -2;
    }

    set_ship_on_map(ship, adm);

    admiral[(int)adm].add_ship(ship);

    if(ship.get() != nullptr)    //admiral non ha accettato il punattore (es. ha gia' 8 navi)
        return -3;
    
    return 0;
}

int GameHandler::gen_ship_c(XY *shipC, XY (&xy)[2], int size, Admirals adm) const 
{
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

int GameHandler::ship_action(Admirals adm, XY (&xy)[2])
{
    if(check_c_oob(xy[0]) || check_c_oob(xy[1])) return -1;
    Hull* h = admiral[(int)adm].defGrid[xy[0].xy[0]][xy[0].xy[1]];
    if(h == nullptr) return -2;
    if(h->getOwner()->is_sunk()) return -3;
    if(h->getOwner()->is_core(h))
        switch((int)(h->getOwner()->get_action())){
            case 0:
                if(int err = action_fire(xy[1], adm))
                    return err -10;
                break;
            case 1:
                if(int err = action_move_heal(h, xy[1], adm))
                    return err -10;
                break;
            case 2:
                if(int err = action_move_search(h, xy[1], adm))
                    return err -10;
                break;
            default: return -5;
        }
    else return -4;
    return 0;
}

int GameHandler::action_fire(XY& xy, Admirals adm)
{
    Admirals enemy(Admirals(((int)adm+1)%2));
    Hull* h = admiral[(int)enemy].defGrid[xy.xy[0]][xy.xy[1]];
    if(h != nullptr){
        h->set_hit();
        admiral[(int)adm].attGrid[xy.xy[0]][xy.xy[1]] = 'X';
    }else admiral[(int)adm].attGrid[xy.xy[0]][xy.xy[1]] = 'O';

    return 0;
}

int GameHandler::action_move_heal(Hull* h, XY& xy, Admirals adm)
{
    if(move_ship(h, xy, adm)){
        heal_aoe(h, adm);
    }else return -2;
    return 0;
}

int GameHandler::action_move_search(Hull* h, XY& xy, Admirals adm)
{
    if(move_ship(h, xy, adm)){
        ricognizione(xy, adm);
    }else return -2;
    return 0;
}

bool GameHandler::move_ship(Hull* h, XY& xy, Admirals adm)
{
    Ship* ship = h->getOwner();
    XY offset = xy - ship->get_hull(ship->get_size()/2)->get_c();

    for(int i = 0; i < ship->get_size(); i++){
        XY c = ship->get_hull(i)->get_c() + offset;
        if(check_c_oob(c) || admiral[(int)adm].defGrid[c.xy[0]][c.xy[1]] != nullptr)
            return false;
    }
    detach_ship_from_map(ship, adm);

    for(int i = 0; i < ship->get_size(); i++){
        XY c = ship->get_hull(i)->get_c() + offset;
        ship->get_hull(i)->set_c(c);
        admiral[(int)adm].defGrid[c.xy[0]][c.xy[1]] = ship->get_hull(i);
    }
    return true;
}

void GameHandler::heal_aoe(Hull* h, Admirals adm)
{
    XY xy = h->get_c();
    for(int r = -1; r < 2; ++r)
        for(int c = -1; c < 2; ++c){
            if(check_c_oob(xy + XY{r,c})) continue;
            Hull* target = admiral[(int)adm].defGrid[xy.xy[0]+r][xy.xy[1]+c];
            if(target != nullptr && target->getOwner() != h->getOwner())
            target->getOwner()->full_heal();
        }
}

void GameHandler::ricognizione(XY& xy, Admirals adm)
{
    for(int r = -2; r < 3; ++r)
        for(int c = -2; c < 3; ++c){
            if(check_c_oob(xy + XY{r,c})) continue;
            if(admiral[((int)adm+1)%2].defGrid[xy.xy[0]+r][xy.xy[1]+c] != nullptr)
            if(admiral[((int)adm+1)%2].defGrid[xy.xy[0]+r][xy.xy[1]+c]->is_hit())
            //come da faq-01/03 
                admiral[(int)adm].attGrid[xy.xy[0]+r][xy.xy[1]+c] = 'X';
            else admiral[(int)adm].attGrid[xy.xy[0]+r][xy.xy[1]+c] = 'Y';
            //ovviamente il sonar rivela anche se *non* ci sono entità
            else admiral[(int)adm].attGrid[xy.xy[0]+r][xy.xy[1]+c] = 0;
        }
}

void GameHandler::display_grids(Admirals adm) const 
{

    //BARRE SUPERIORI
    std::cout << "\t----GRIGLIA DI DIFESA----\t----GRIGLIA D'ATTACCO----\n" << std::endl;
    std::cout << "\t";

    for(int c = 0; c < GRIDSIZE; ++c) std::cout << ' ' <<  (c+1)%10;
    std::cout << "\t";
    for(int c = 0; c < GRIDSIZE; ++c) std::cout << ' ' <<  (c+1)%10;

    //GRIGLIA DI ATTACCO
    std::cout << "\n";
    for(int i = 0; i < GRIDSIZE; ++i)
    {
        std::cout << (char)('A' + i);
        std::cout << "\t";
        for(int c = 0; c < GRIDSIZE; ++c){
            if (admiral[(int)adm].defGrid[i][c] == nullptr) std::cout << " ~";
            else switch(admiral[(int)adm].defGrid[i][c]->getOwner()->get_size())
            {
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
        //GRIGLIA DI DIFESA
        std::cout << "\t";
        for(int c = 0; c < GRIDSIZE; ++c){
            if (admiral[(int)adm].attGrid[i][c] == 0) std::cout << " ~";
            else std::cout << ' ' << admiral[(int)adm].attGrid[i][c];
        }
        std::cout << std::endl;;
    }
    return;
}

void GameHandler::clear_att_grid(Admirals adm)
{
    for(int i = 0; i < GRIDSIZE; ++i)
        for(int c = 0; c < GRIDSIZE; ++c)
            admiral[adm].attGrid[i][c] = 0;
    return;
}

void GameHandler::clear_sonar(Admirals adm)
{
    for(int i = 0; i < GRIDSIZE; ++i)
        for(int c = 0; c < GRIDSIZE; ++c)
            if(admiral[adm].attGrid[i][c] == 'Y')
                admiral[adm].attGrid[i][c] = 0;
    return;
}

void GameHandler::remove_all_sunk(Admirals adm) 
//volendo aggiungere cout di segnalazione affondamento
{ 
    for(int i = 0 ; i < SHIPSN/2; ++i){
        Ship* shipTarget = admiral[(int)adm].ships[i];

        if(shipTarget != nullptr && shipTarget->is_sunk()){
            detach_ship_from_map(shipTarget, adm);

            for(int c = 0; c < cores.size(); ++c){
                if(shipTarget->get_hull(shipTarget->get_size()/2) == cores.at(c)){
                    cores.erase(cores.begin()+c);
                    break;
                }
            }

            admiral[(int)adm].delete_ship(shipTarget);
        }
    }
}

void GameHandler::set_ship_on_map(std::unique_ptr<Ship>& ship, Admirals adm)
{
    //fa si che le corrette caselle della gliglia di difesa puntino ai relativi scafi che le occupano  (movimento e creazione)
    for(int i = 0; i < ship->get_size(); i++){
        XY c = ship->get_hull(i)->get_c();
        admiral[(int)adm].defGrid[c.xy[0]][c.xy[1]] = ship->get_hull(i);
    }
}

void GameHandler::set_ship_on_map(Ship* ship, Admirals adm)
{
    //fa si che le corrette caselle della gliglia di difesa puntino ai relativi scafi che le occupano  (movimento e creazione)
    for(int i = 0; i < ship->get_size(); i++){
        XY c = ship->get_hull(i)->get_c();
        admiral[(int)adm].defGrid[c.xy[0]][c.xy[1]] = ship->get_hull(i);
    }
}

void GameHandler::detach_ship_from_map(Ship* ship, Admirals adm)
{
    //setta le caselle della griglia che al momento puntano allo scafo di ship a nullptr (movimento e distruzione) 
    for(int i = 0; i < ship->get_size(); ++i){
        XY c = ship->get_hull(i)->get_c();
        admiral[(int)adm].defGrid[c.xy[0]][c.xy[1]] = nullptr;
    }
}

void GameHandler::set_cores()
{
    for(int i = 0; i < 2; ++i)
        for(int c = 0; c < SHIPSN/2; ++c)
            if(admiral[i].ships[c] != nullptr) cores.push_back(admiral[i].ships[c]->get_hull(admiral[i].ships[c]->get_size()/2));
}

Hull* GameHandler::get_core(int i)
{
    return cores.at(i);
}

bool GameHandler::next_turn() 
{
    if(turn > MAXTURNS) return false; 
    ++turn;
    return true; 
}

bool GameHandler::is_winner(Admirals adm) 
{
    if(admiral[Admirals((adm + 1)%2)].shipC == 0) return true; 
    return false; 
}

void GameHandler::flip_coin() 
{
    coin = rand()%2; 
    return; 
}

GameHandler::Bot::Bot(GameHandler* gh) : gh (gh){}

int GameHandler::Bot::get_ship_pos(char *inp)
{
    XY xy[2];
    gen_rand_ship_coord(xy);
    coord_to_char(xy, inp);
    std::cout << "Bot input." << std::endl;
    return 0;
}

int GameHandler::Bot::get_ship_act(char *inp)
{
    XY xy[2];
    gen_rand_coord(xy);
    coord_to_char(xy, inp);
    std::cout << "Bot input." << std::endl;
    return 0;
}

void GameHandler::Bot::gen_rand_ship_coord(XY (&xy)[2]) const 
{
    xy[0].xy[0] = rand() % GRIDSIZE;
    xy[0].xy[1] = rand() % GRIDSIZE;
    xy[1] = xy[0];

    int dim = rand()%2;     //orientamento della nave, asse x o y
    int type;               //tipo nave

    if(gh->get_turn() < CORA) type = 2;
    else if(gh->get_turn() < SUPP + CORA) type = 1;
    else if(gh->get_turn() < SHIPSN) type = 0;

    xy[1].xy[dim] += type*2; 
    if(check_c_oob(xy[1])) xy[1].xy[dim] -= type*4; 

    //std::cout << "\n" << xy[0].xy[0] << ' '  << xy[0].xy[1] << ' '  << xy[1].xy[0] << ' '  << xy[1].xy[1] << ' ' << gh->get_turn() << '\n';
}

void GameHandler::Bot::gen_rand_coord(XY (&xy)[2]) const 
{
    if(Admirals((gh->get_turn() + gh->get_coin())%2) == RedAdm)
        xy[0] = gh->get_core(rand()%gh->get_active_ships_n(RedAdm))->get_c();
    else
        xy[0] = gh->get_core(gh->get_active_ships_n(RedAdm) + rand()%gh->get_active_ships_n(BlueAdm))->get_c();
    xy[1].xy[0] = rand() % GRIDSIZE;
    xy[1].xy[1] = rand() % GRIDSIZE;
}