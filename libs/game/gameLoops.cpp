#include "gameLoops.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

void gameLoops::game_loop(bool pc)
{
    GameHandler gh{};
    OutLogger ol{};
    std::unique_ptr<Player> player[2];
    
    if(pc) player[0] = std::make_unique<HumanPlayer>();

    //il bot che sostituisce l'umano non e' clever
    else player[0] = std::make_unique<GameHandler::Bot>(&gh);
    //il secondo bot e' clever. Il giocatore iniziale e' scelto a caso,
    //quindi non sara' necessariamente il giocatore 2 
    player[1] = std::make_unique<GameHandler::CleverBot>(&gh);

    gh.flip_coin();
    char playerInput[6];

    Log::reset_log_file();
    ol.log_coin(gh.get_coin());
    
    if(pc)
    {
        std::cout << "\n\n-----INTRODUZIONE-----" << std::endl;
        //WIP 
        std::cout << "\n-Leggenda simboli-\n"
                    << "\nZone griglia di difesa:\n"
                    << "\t~: dove non è presente una nave alleata;\n"
                    << "\tC: occupata da una corazzata;\n"
                    << "\t@: danneggiata di una corazzata;\n"
                    << "\tS: occupata da una nave di supporto;\n"
                    << "\t$: danneggiata di una nave di supporto;\n"
                    << "\tE: occupata da un sottomarino di esplorazione;\n"
                    << "\t£: danneggiata di un sottomarino di esplorazione.\n"
                    << "\nZone griglia di attacco:\n"
                    << "\t~: dove non sono state rilevate navi nemiche;\n"
                    << "\tX: dove una corazzata alleata ha colpito una una nave nemica;\n"
                    << "\tO: dove una corazzata alleata ha colpito a vuoto;\n"
                    << "\tY: dove un sottomarino alleato ha rilevato una nave nemica."
                    << std::endl;
        std::cout << "\nLista comandi speciali:\n"
                    << "\tXX XX: Mostra griglie di attacco e di difesa;\n"
                    << "\tYY YY: Rimuove i simboli 'Y' dalla griglia di attacco;\n"
                    << "\tZZ ZZ: Rimuove tutti i simboli dalla griglia di attacco.\n"
                    << std::endl;

        std::cout << "Premi invio per iniziare la partita.\n";
        std::cin.ignore(264, '\n');
    }

    std::cout << "\n-----Fase di schieramento-----" << std::endl;
    init_loop(player, gh, ol, playerInput, pc);
    std::cout << "\n\n-----Fase di combattimento-----" << std::endl;
    main_loop(player, gh, ol, playerInput, pc);
}

void gameLoops::init_loop(const std::unique_ptr<Player> (&player)[2], GameHandler& gh, OutLogger& ol,  char (&playerInput)[6], bool pc)
{
    int shipType = 2;
    int once = -1;

    while(gh.get_turn() < SHIPS_TOT && gh.get_turn() < MAXTURNS)
    { 
        Admirals activePlayer = gh.getCurrentPlayer();

        if(once != gh.get_turn())
        {
            if(gh.get_turn() == CORA) --shipType;
            if(gh.get_turn() == SUPP+CORA) --shipType;
            if(pc)
            {
                std::cout << "\nGiocatore " << activePlayer + 1 << ", Turno " << gh.get_turn() + 1 <<  ".\n"; 
                std::cout << "Inserire coppia di coordinate oppure un comando speciale." << std::endl;
                std::cout << "Coordinate ";
                if(gh.get_turn() < CORA) std::cout << "corazzata: ";
                else if(gh.get_turn() < SUPP + CORA)  std::cout << "nave di supporto: ";
                else if(gh.get_turn() < SHIPS_TOT) std::cout << "sottomarino di esplorazione: ";
            }
            ++once;
        }

        if(int err = player[activePlayer]->get_ship_pos(playerInput))
        {
            //std::cout << "Formato input non valido: " << err << std::endl;
            if(pc) std::cout << "Formato input non valido. Riprova: ";
            continue;
        }

        XY xy[2];

        char_to_coord(xy, playerInput);

        if(pc)
        {
            if(xy[0]==XY{-1, -1}){
                std::cout << "\n" << std::endl;
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
        }

        if(int err = gh.set_ship(activePlayer, ShipType(shipType), xy))
        {
            //std::cout << "Posizione non valida: " << err << std::endl;
            if(pc) std::cout << "Posizione non valida. Riprova: ";
            continue;
        }

        if(pc) std::cout << "Schieramento riuscito." << std::endl;
        ol.log_cinput(playerInput);
        gh.next_turn();
    }
}

void gameLoops::main_loop(const std::unique_ptr<Player> (&player)[2], GameHandler& gh, OutLogger& ol, char (&playerInput)[6], bool pc)
{
    gh.set_cores();
    int once = gh.get_turn()-1;

    while(gh.get_turn() < MAXTURNS){
        Admirals activePlayer = gh.getCurrentPlayer();

        if(once != gh.get_turn())
        {
            if(pc)
            {
                std::cout << "\nGiocatore " << activePlayer + 1 << ", Turno " << gh.get_turn() + 1 <<  ".\n"; 
                std::cout << "Inserire coppia di coordinate oppure un comando speciale." << std::endl;
                std::cout << "Coordinate nave e bersaglio:  ";
            }
            ++once;
        }

        if(int err = player[activePlayer]->get_ship_act(playerInput))
        {
            //std::cout << "Formato input non valido: " << err << std::endl;
            if(pc) std::cout << "Formato input non valido. Riprova: ";
            continue;
        }

        XY xy[2];

        char_to_coord(xy, playerInput);

        if(pc)
        {
            if(xy[0]==XY{-1, -1}){
                std::cout << "\n" << std::endl;
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
        }

        if(int err = gh.ship_action(activePlayer, xy))
        {
            //std::cout << "Coordinate non valide: " << err << std::endl;
            if(pc) std::cout << "Coordinate non valide. Riprova: ";
            continue;
        }
        
        if(pc) std::cout << "Azione avvenuta." << std::endl;

        ol.log_cinput(playerInput);

        gh.remove_all_sunk(Admirals((activePlayer + 1)%2));

        if(gh.is_winner(activePlayer))
        {
            std::cout << "\nVince il giocatore " << activePlayer + 1 << "!" << std::endl;
            return;
        }
        gh.next_turn();
    }
}
