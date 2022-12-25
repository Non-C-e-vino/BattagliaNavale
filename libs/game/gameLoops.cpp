#include "gameLoops.h"

void gameLoops::init_loop(const std::unique_ptr<Player> &player1, const std::unique_ptr<Player> &player2, GameHandler& gh){
    player1->get_input();
}

void gameLoops::main_loop(const std::unique_ptr<Player> &player1, const std::unique_ptr<Player> &player2, GameHandler& gh){
    player1->get_input();
}

void gameLoops::game_loop(bool pc){
    GameHandler gh{};
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    if(pc) player1 = std::make_unique<HumanPlayer>();
    else player1 = std::make_unique<Bot>();
    player2 = std::make_unique<Bot>();
    init_loop(player1, player2, gh);
    main_loop(player1, player2, gh);
}

