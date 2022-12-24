#include "gameLoops.h"

void gameLoops::initLoop(const std::unique_ptr<Player> &player1, const std::unique_ptr<Player> &player2){
    player1->getInput();
}

void gameLoops::mainLoop(){

}

void gameLoops::gameLoop(bool pc){
    std::unique_ptr<Player> player1;
    std::unique_ptr<Player> player2;
    if(pc) player1 = std::make_unique<HumanPlayer>();
    else player1 = std::make_unique<Bot>();
    player2 = std::make_unique<Bot>();
    initLoop(player1, player2);
    mainLoop();
}

