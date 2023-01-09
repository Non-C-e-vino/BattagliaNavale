#include "gameLoops.h"
#include "logger.h"
#include <cstdlib>
#include <ctime>

void gameLoops::game_loop(bool pc)
{
    GameHandler gh{};
    std::unique_ptr<Player> player[2];
    
    if(pc) player[0] = std::make_unique<HumanPlayer>();
    else player[0] = std::make_unique<GameHandler::Bot>(&gh);
<<<<<<< HEAD
    player[1] = std::make_unique<GameHandler::CleverBot>(&gh);
=======
    player[1] = std::make_unique<GameHandler::Bot>(&gh);
>>>>>>> 8b746e5ccba67772300698f4480711b8dddca19e

    std::srand(time(NULL));
    gh.flip_coin();
    char playerInput[6];

    Log::reset_log_file();
    Log::log_coin(gh.get_coin());
    
    std::cout << "\n\n-----Fase di schieramento-----" << std::endl;
    init_loop(player, gh, playerInput);
    std::cout << "\n\n-----Fase di combattimento-----" << std::endl;
    main_loop(player, gh, playerInput);
}

void gameLoops::init_loop(const std::unique_ptr<Player> (&player)[2], GameHandler& gh, char (&playerInput)[6])
{
    int shipType = 2;
    int once = -1;

    while(gh.get_turn() < SHIPSN && gh.get_turn() < MAXTURNS)
    { 
        Admirals activePlayer = Admirals((gh.get_turn() + gh.get_coin())%2);

        if(once != gh.get_turn())
        {
            if(gh.get_turn() == CORA) --shipType;
            if(gh.get_turn() == SUPP+CORA) --shipType;
            std::cout << "\nGiocatore " << activePlayer + 1 << ", Turno " << gh.get_turn() + 1 <<  ".\n"; 
            std::cout << "Inseri coppia di coordinate oppure [XX XX] [YY YY] [ZZ ZZ]" << std::endl;
            std::cout << "Coordinate ";
            if(gh.get_turn() < CORA) std::cout << "corazzata: ";
            else if(gh.get_turn() < SUPP + CORA)  std::cout << "nave di supporto: ";
            else if(gh.get_turn() < SHIPSN) std::cout << "sottomarino di esplorazione: ";
            ++once;
        }

        if(int err = player[activePlayer]->get_ship_pos(playerInput))
        {
            //std::cout << "Formato input non valido: " << err << std::endl;
            std::cout << "Formato input non valido. Riprova: ";
            continue;
        }

        XY xy[2];

        coord_convert(xy, playerInput);
 
        if(xy[0]==XY{-1, -1}){
            gh.display_grids(activePlayer);
            continue;
        }
        if(xy[0]==XY{-2, -2}){
            gh.clear_sonar(activePlayer);
            continue;
        }
        if(xy[0]==XY{-3, -3}){
            gh.clear_att_grid(activePlayer);
            continue;
        }

        if(int err = gh.set_ship(activePlayer, ShipType(shipType), xy))
        {
            //std::cout << "Posizione non valida: " << err << std::endl;
            std::cout << "Posizione non valida. Riprova: ";
            continue;
        }

        std::cout << "Schieramento riuscito." << std::endl;
        Log::log_cinput(playerInput);
        gh.next_turn();
    }
}

void gameLoops::main_loop(const std::unique_ptr<Player> (&player)[2], GameHandler& gh, char (&playerInput)[6])
{
    gh.set_cores();
    int once = gh.get_turn()-1;

    while(gh.get_turn() < MAXTURNS){
        Admirals activePlayer = Admirals((gh.get_turn() + gh.get_coin())%2);

        if(once != gh.get_turn()){
            std::cout << "\nGiocatore " << activePlayer + 1 << ", Turno " << gh.get_turn() + 1 <<  ".\n"; 
            std::cout << "Inserire coppia di coordinate oppure [XX XX] [YY YY] [ZZ ZZ]" << std::endl;
            std::cout << "Coordinate nave e bersaglio:  ";
            ++once;
        }

        if(int err = player[activePlayer]->get_ship_act(playerInput))
        {
            //std::cout << "Formato input non valido: " << err << std::endl;
            std::cout << "Formato input non valido. Riprova: ";
            continue;
        }

        XY xy[2];

        coord_convert(xy, playerInput);

        if(xy[0]==XY{-1, -1}){
            gh.display_grids(activePlayer);
            continue;
        }
        if(xy[0]==XY{-2, -2}){
            gh.clear_sonar(activePlayer);
            continue;
        }
        if(xy[0]==XY{-3, -3}){
            gh.clear_att_grid(activePlayer);
            continue;
        }

        if(int err = gh.ship_action(activePlayer, xy))
        {
            //std::cout << "Coordinate non valide: " << err << std::endl;
            std::cout << "Coordinate non valide. Riprova: ";
            continue;
        }
        std::cout << "Azione avvenuta." << std::endl;
        Log::log_cinput(playerInput);

        gh.remove_all_sunk(Admirals((activePlayer + 1)%2));

        if(gh.is_winner(activePlayer))
        {
            std::cout << "\nVince il giocatore " << activePlayer + 1 << "!" << std::endl;
            return;
        }
        gh.next_turn();
    }
}