#include "gameLoops.h"
#include "logger.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>
#include <cctype>

void gameLoops::game_loop(bool pc){
    GameHandler gh{};
    std::unique_ptr<Player> player[2];
    
    if(pc) player[0] = std::make_unique<HumanPlayer>();
    else player[0] = std::make_unique<Bot>(&gh);
    player[1] = std::make_unique<Bot>(&gh);

    srand(time(NULL));
    gh.flip_coin();
    char playerInput[6];

    Log::reset_log_file();
    
    std::cout << "\n\n-----Fase di schieramento-----" << std::endl;
    init_loop(player, gh, playerInput);
    std::cout << "\n\n-----Fase di combattimento-----" << std::endl;
    main_loop(player, gh, playerInput);
}

void gameLoops::replay_loop(std::string& fileName, bool delay){
    GameHandler gh{};
    Logger l(fileName);
    char playerInput[6];
    
    std::cout << "\n\n-----Fase di schieramento-----" << std::endl;
    replay_init_loop(l, gh, playerInput, delay);
    std::cout << "\n\n-----Fase di combattimento-----" << std::endl;
    replay_main_loop(l, gh, playerInput, delay);
}

void gameLoops::init_loop(const std::unique_ptr<Player> (&player)[2], GameHandler& gh, char (&playerInput)[6]){

    int shipType = 2;
    int once = -1;

    while(gh.get_turn() < SHIPSN && gh.get_turn() < MAXTURNS){ 

        Admirals activePlayer = Admirals((gh.get_turn() + gh.get_coin())%2);

        if(once != gh.get_turn()){
            if(gh.get_turn() == CORA) --shipType;
            if(gh.get_turn() == SUPP+CORA) --shipType;
            std::cout << "\nGiocatore " << activePlayer + 1 << ", Turno " << gh.get_turn() + 1 <<  ".\n"; 
            std::cout << "Inseri coppia di coordinate oppure [XX XX] [YY YY] [ZZ ZZ]" << std::endl;
            std::cout << "Coordinate ";
            switch(gh.get_turn()/6){
                case 0: std::cout << "corazzata: ";
                break;
                case 1: std::cout << "nave di supporto: ";
                break;
                case 2: std::cout << "sottomarino di esplorazione: ";
                break;
            }
            ++once;
        }

        if(int err = player[activePlayer]->get_ship_pos(playerInput)){
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
            gh.clear_att_grid(activePlayer);
            continue;
        }
        if(xy[0]==XY{-3, -3}){
            gh.clear_miss_sonar(activePlayer);
            continue;
        }

        if(int err = gh.set_ship(activePlayer, ShipType(shipType), xy)){
            //std::cout << "Posizione non valida: " << err << std::endl;
            std::cout << "Posizione non valida. Riprova: ";
            continue;
        }
        std::cout << "Schieramento riuscito." << std::endl;
        gh.display_grids(activePlayer); //TEMP
        Log::log(playerInput);
        gh.next_turn();
    }
}

void gameLoops::main_loop(const std::unique_ptr<Player> (&player)[2], GameHandler& gh, char (&playerInput)[6]){
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

        if(int err = player[activePlayer]->get_ship_act(playerInput)){
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
            gh.clear_att_grid(activePlayer);
            continue;
        }
        if(xy[0]==XY{-3, -3}){
            gh.clear_miss_sonar(activePlayer);
            continue;
        }
        if(int err = gh.ship_action(activePlayer, xy)){
            //std::cout << "Coordinate non valide: " << err << std::endl;
            std::cout << "Coordinate non valide. Riprova: ";
            continue;
        }
        Log::log(playerInput);
        //gh.display_grids(Admirals((gh.get_turn() + gh.get_coin() + 1)%2)); //TEMP
        std::cout << "Azione avvenuta." << std::endl;
        gh.remove_all_sunk(Admirals((activePlayer + 1)%2));
        if(gh.game_end(Admirals((activePlayer + 1)%2))){
            std::cout << "\nVince il giocatore " << activePlayer + 1 << "!" << std::endl;
            return;
        }
        
        gh.next_turn();
    }
}

void gameLoops::replay_init_loop(Logger & l, GameHandler& gh, char (&playerInput)[6], bool delay){

    int shipType = 2;

    while(gh.get_turn() < SHIPSN && gh.get_turn() < MAXTURNS){ 

        Admirals activePlayer = Admirals((gh.get_turn())%2);

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

        if(l.read_log(playerInput)){
            std::cout << "Partita tarminata prematuramente."<< std::endl;
            return;
        }

        std::cout << playerInput[0];
        for(int i = 1; i < 6 && playerInput[i] != '\0'; ++i){
            if(std::isalpha(playerInput[i])) std::cout << ' ';
            std::cout << playerInput[i];
        }
        std::cout << "\n "<< std::endl;

        XY xy[2];

        coord_convert(xy, playerInput);

        gh.set_ship(activePlayer, ShipType(shipType), xy);
        gh.display_grids(activePlayer);
        gh.next_turn();

        if(delay) std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void gameLoops::replay_main_loop(Logger & l, GameHandler& gh, char (&playerInput)[6], bool delay){

    gh.set_cores();

    while(gh.get_turn() < MAXTURNS){
        Admirals activePlayer = Admirals((gh.get_turn() + gh.get_coin())%2);

        std::cout << "\nGiocatore " << activePlayer + 1 << ", Turno " << gh.get_turn() + 1 <<  ".\n"; 
        std::cout << "Coordinate nave e bersaglio:  ";

        if(l.read_log(playerInput)){
            std::cout << "Partita tarminata prematuramente."<< std::endl;
            return;
        }
        
        std::cout << playerInput[0];
        for(int i = 1; i < 6 && playerInput[i] != '\0'; ++i){
            if(std::isalpha(playerInput[i])) std::cout << ' ';
            std::cout << playerInput[i];
        }
        std::cout << "\n "<< std::endl;

        XY xy[2];

        coord_convert(xy, playerInput);

        gh.ship_action(activePlayer, xy);
        gh.remove_all_sunk(Admirals((activePlayer + 1)%2));
        gh.display_grids(activePlayer);

        if(gh.game_end(Admirals((activePlayer + 1)%2)) || gh.game_end(activePlayer)){
            std::cout << "\nVince il giocatore " << activePlayer + 1 << "!" << std::endl;
            return;
        }
        gh.next_turn();

        if(delay) std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}