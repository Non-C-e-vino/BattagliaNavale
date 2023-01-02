#include "gameLoops.h"
#include <cstdlib>
#include <ctime>
#include "logger.h"
void gameLoops::game_loop(bool pc){
    GameHandler gh{};
    std::unique_ptr<Player> player[2];
    
    if(pc) player[0] = std::make_unique<HumanPlayer>();
    else player[0] = std::make_unique<Bot>(&gh);
    player[1] = std::make_unique<Bot>(&gh);

    srand(time(NULL));
    Logger l;
    gh.flip_coin();
    char playerInput[6];
    
    std::cout << "\n\n-----Fase di schieramento-----" << std::endl;
    init_loop(player, gh, l, playerInput);
    std::cout << "\n\n-----Fase di combattimento-----" << std::endl;
    main_loop(player, gh, l, playerInput);
}

void gameLoops::replay_loop(){
    /*GameHandler gh{};
    std::unique_ptr<Player> player[2];

    player[0] = std::make_unique<Replayer>();
    player[1] = std::make_unique<Replayer>();
    
    std::cout << "---Fase preparatoria---" << std::endl;
    init_loop(player, gh, );
    std::cout << "---Fase di combattimento---" << std::endl;
    main_loop(player, gh);*/
}

void gameLoops::init_loop(const std::unique_ptr<Player> (&player)[2], GameHandler& gh, Logger& l, char (&playerInput)[6]){

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
                case 2: std::cout << "Sottomarino di esplorazione: ";
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
        l.log(playerInput);
        gh.next_turn();
    }
}

void gameLoops::main_loop(const std::unique_ptr<Player> (&player)[2], GameHandler& gh, Logger& l, char (&playerInput)[6]){

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
        std::cout << "Azione avvenuta." << std::endl;
        gh.remove_all_sunk(Admirals((activePlayer + 1)%2));
        if(gh.game_end(Admirals((activePlayer + 1)%2))){
            std::cout << "Vince il giocatore " << activePlayer + 1 << "!" << std::endl;
            return;
        }
        gh.display_grids(Admirals((gh.get_turn() + gh.get_coin() + 1)%2)); //TEMP
        l.log(playerInput);
        gh.next_turn();
    }
}