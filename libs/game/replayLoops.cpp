#include "replayLoops.h"
#include "logger.h"
#include <thread>
#include <chrono>
#include <iostream>


void gameLoops::replay_loop(std::string& fileName, int delay)
{
    GameHandler gh{};
    InLogger l(fileName);
    char playerInput[6];

    if(gh.set_coin(l.read_coin_log()) == -1) 
        gh.set_coin(0);
    
    std::cout << "\n\n-----Fase di schieramento-----" << std::endl;
    replay_init_loop(l, gh, playerInput, delay);
    std::cout << "\n\n-----Fase di combattimento-----" << std::endl;
    replay_main_loop(l, gh, playerInput, delay);
}

void gameLoops::replay_init_loop(InLogger & l, GameHandler& gh, char (&playerInput)[6], int delay)
{
    int shipType = 2;

    while(gh.get_turn() < SHIPS_TOT && gh.get_turn() < MAXTURNS)
    {
        Admirals activePlayer = gh.getCurrentPlayer();

        if(gh.get_turn() == CORA) --shipType;
        if(gh.get_turn() == SUPP+CORA) --shipType;
        std::cout << "\nGiocatore " << activePlayer + 1 << ", Turno " << gh.get_turn() + 1 <<  ".\n"; 
        std::cout << "Coordinate ";
        switch(gh.get_turn()/6){
            case 0: std::cout << "corazzata: ";
            break;
            case 1: std::cout << "nave di supporto: ";
            break;
            case 2: std::cout << "sottomarino di esplorazione: ";
            break;
        }

        if(l.read_log(playerInput))
        {
            std::cout << "Partita tarminata prematuramente."<< std::endl;
            return;
        }

        print_char_coord(playerInput);

        std::cout << "\n" << std::endl;

        XY xy[2];

        char_to_coord(xy, playerInput);

        if(check_c_oob(xy[0]) || check_c_oob(xy[0]) || gh.set_ship(activePlayer, ShipType(shipType), xy))
        {
            std::cout << "File log corrotto."<< std::endl;
            //si postrebbe anche valutare il lancio di un eccezione.
            return;
        }

        gh.display_grids(activePlayer);
        gh.next_turn();

        if(delay) std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void gameLoops::replay_main_loop(InLogger & l, GameHandler& gh, char (&playerInput)[6], int delay)
{
    gh.set_cores();

    while(gh.get_turn() < MAXTURNS)
    {
        Admirals activePlayer = gh.getCurrentPlayer();

        std::cout << "\nGiocatore " << activePlayer + 1 << ", Turno " << gh.get_turn() + 1 <<  ".\n"; 
        std::cout << "Coordinate nave e bersaglio:  ";

        if(l.read_log(playerInput))
        {
            std::cout << "Partita tarminata prematuramente."<< std::endl;
            return;
        }
        
        print_char_coord(playerInput);

        std::cout << "\n" << std::endl;

        XY xy[2];

        char_to_coord(xy, playerInput);

        if(check_c_oob(xy[0]) || check_c_oob(xy[0]) || gh.ship_action(activePlayer, xy))
        {
            std::cout << "File log corrotto."<< std::endl;
            //si postrebbe anche valutare il lancio di un eccezione.
            return;
        }

        gh.remove_all_sunk(Admirals((activePlayer + 1)%2));
        gh.display_grids(activePlayer);

        if(gh.is_winner(activePlayer))
        {
            std::cout << "\nVince il giocatore " << activePlayer + 1 << "!" << std::endl;
            return;
        }
        gh.next_turn();

        if(delay) std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}