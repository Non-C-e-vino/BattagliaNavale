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
    gh.throw_coin();
    char playerInput[6];
    
    std::cout << "---Fase preparatoria---" << std::endl;
    init_loop(player, gh, l, playerInput);
    std::cout << "---Fase di combattimento---" << std::endl;
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

    for(int i = 0, once = -1; i < SHIPSN;){

        if(once != i){
            std::cout << "\nGiocatore " << (i + gh.get_coin())%2 +1<< ",\n"; 
            std::cout << "inserire coppia di coordinate oppure [XX XX] [YY YY] [ZZ ZZ]" << std::endl;
            std::cout << "Coordinate nave " << i/2 + 1;
            switch(i/6){
                case 0: std::cout << ", corazzata: ";
                break;
                case 1: std::cout << ", nave di supporto: ";
                break;
                case 2: std::cout << ", sottomarino: ";
                break;
            }
            ++once;
        }

        if(int err = player[(i + gh.get_coin())%2]->get_ship_pos(playerInput)){
            std::cout << "Formato input non valido: " << err << std::endl;
            continue;
        }

        XY xy[2];

        coord_convert(xy, playerInput);

        //std::cout << "\n" << (i + coin)%2 << ' ' << xy[0].xy[0] << ' '  << xy[0].xy[1] << ' '  << xy[1].xy[0] << ' '  << xy[1].xy[1] << '\n';
 
        if(xy[0]==XY{-1, -1}){
            gh.display_grids(Admirals((i + gh.get_coin())%2));
            continue;
        }
        if(xy[0]==XY{-2, -2}){
            gh.clear_att_grid(Admirals((i + gh.get_coin())%2));
            continue;
        }
        if(xy[0]==XY{-3, -3}){
            gh.clear_miss_sonar(Admirals((i + gh.get_coin())%2));
            continue;
        }

        if(int err = gh.set_ship(Admirals((i + gh.get_coin())%2), ShipType(2 - i/6), xy)){
            std::cout << "Posizione non valida: " << err << std::endl;
            continue;
        }
        std::cout << "Schieramento riuscito." << std::endl;
        gh.display_grids(Admirals((i + gh.get_coin())%2)); //TEMP
        gh.next_turn();
        ++i;
        l.log(playerInput);
    }
}

void gameLoops::main_loop(const std::unique_ptr<Player> (&player)[2], GameHandler& gh, Logger& l, char (&playerInput)[6]){

    gh.set_cores();

    for(int i = gh.get_turn(), once = gh.get_turn()-1; i < MAXTURNS;){
        if(once != i){
            std::cout << "\nGiocatore " << (i + gh.get_coin())%2 +1<< ",\n"; 
            std::cout << "inserire coppia di coordinate oppure [XX XX] [YY YY] [ZZ ZZ]" << std::endl;
            std::cout << "Coordinate nave e bersaglio:  ";
            ++once;
        }

        if(int err = player[(i + gh.get_coin())%2]->get_ship_act(playerInput)){
            std::cout << "Formato input non valido: " << err << std::endl;
            continue;
        }

        XY xy[2];

        coord_convert(xy, playerInput);

        //std::cout << "\n" << (i + coin)%2 << ' ' << xy[0].xy[0] << ' '  << xy[0].xy[1] << ' '  << xy[1].xy[0] << ' '  << xy[1].xy[1] << '\n';
 
        if(xy[0]==XY{-1, -1}){
            gh.display_grids(Admirals((i + gh.get_coin())%2));
            continue;
        }
        if(xy[0]==XY{-2, -2}){
            gh.clear_att_grid(Admirals((i + gh.get_coin())%2));
            continue;
        }
        if(xy[0]==XY{-3, -3}){
            gh.clear_miss_sonar(Admirals((i + gh.get_coin())%2));
            continue;
        }

        if(int err = gh.ship_action(Admirals((i + gh.get_coin())%2), xy)){
            std::cout << "Coordinate non valide: " << err << std::endl;
            continue;
        }
        std::cout << "Azione avvenuta." << std::endl;
        gh.display_grids(Admirals((i + gh.get_coin())%2)); //TEMP
        gh.next_turn();
        ++i;
        l.log(playerInput);
    }
}

