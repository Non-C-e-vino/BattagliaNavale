#include "gameHandler.h"
#include <iostream>
#include <ctime>
#include <cstdlib>


GameHandler::Bot::Bot(GameHandler* gh) : gh (gh){}

int GameHandler::Bot::get_ship_pos(char *inp)
{
    XY xy[2];
    gen_rand_ship_coord(xy);
    coord_to_char(xy, inp);
    //std::cout << "Bot input." << std::endl;
    return 0;
}

int GameHandler::Bot::get_ship_act(char *inp)
{
    XY xy[2];
    gen_rand_coord(xy);
    coord_to_char(xy, inp);
    //std::cout << "Bot input." << std::endl;
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
    else if(gh->get_turn() < SHIPS_TOT) type = 0;

    xy[1].xy[dim] += type*2; 
    if(check_c_oob(xy[1])) xy[1].xy[dim] -= type*4; 

    //std::cout << "\n" << xy[0].xy[0] << ' '  << xy[0].xy[1] << ' '  << xy[1].xy[0] << ' '  << xy[1].xy[1] << '\n';
}

void GameHandler::Bot::gen_rand_coord(XY (&xy)[2]) const
{
    if(gh->getCurrentPlayer(gh->get_turn(), gh->GameHandler::get_coin())== RedAdm)
        xy[0] = gh->get_core(rand()%gh->get_active_ships_n(RedAdm))->get_c();
    else
        xy[0] = gh->get_core(gh->get_active_ships_n(RedAdm) + rand()%gh->get_active_ships_n(BlueAdm))->get_c();
    xy[1].xy[0] = rand() % GRIDSIZE;
    xy[1].xy[1] = rand() % GRIDSIZE;

    //std::cout << "\n" << xy[0].xy[0] << ' '  << xy[0].xy[1] << ' '  << xy[1].xy[0] << ' '  << xy[1].xy[1] << ' ' << gh->get_turn() << '\n';
}

GameHandler::CleverBot::CleverBot(GameHandler* gh) : Bot(gh){};


int GameHandler::CleverBot::get_ship_act(char *inp)
{
    XY xy[2];
    gen_clever_coord(xy);
    coord_to_char(xy, inp);
    //std::cout << "Bot input." << std::endl;
    return 0;
}

void GameHandler::CleverBot::gen_clever_coord(XY (&xy)[2])
{
    gen_rand_coord(xy);

    Admirals activePlayer =gh->getCurrentPlayer(gh->get_turn(), gh->get_coin());
    
    ShipAction action = gh->admiral[activePlayer].defGrid[xy[0].xy[0]][xy[0].xy[1]]->getOwner()->get_action();

    //WIP: se sono presenti, l'azione viene riassegnata ad uno dei ricognitori.
    //avviene solo se una scan e' necessaria
    /*if(!hasScanned && !shootingTime){
        
        //TODO: metodo Admiral getCurrentPlayer() in GameHandler

    }*/

    if(action == ShipAction::Fire)
    {
        //se dovrebbe essere avvenuta una scansione e non ho bersagli disponibili
        if(hasScanned && !shootingTime)
        {
            //aggiorno la lista bersagli
            for(int r = 0; r < GRIDSIZE; ++r)
                for(int c = 0; c < GRIDSIZE; ++c)
                    if(gh->admiral[activePlayer].attGrid[r][c] == 'Y') targets.insert(XY{r,c});
            hasScanned = false;
            shootingTime = true;
        }

        //la lista dei bersagli potrebbe essere vuota anche subito dopo l'aggiornamento
        if(targets.empty())
            shootingTime = false;
        else
        {
            //"aggiusto" la mira della corazzata
            //Il bersaglio e' scelto a caso per evitare che
            //il bot diventi prevedibile
            std::set<XY>::iterator iter = targets.begin();
            std::advance(iter, std::rand()%targets.size());
            xy[1] = *iter;
            targets.erase(iter);
        }
    }

    //non garantisce ne' che l'azione sia effettivamente avvenuta
    //ne' che abbia rilevato nemici
    if(action == ShipAction::MoveAndSearch)
    {
        hasScanned = true;
    }
}
