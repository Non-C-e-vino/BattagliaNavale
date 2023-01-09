#ifndef GAMELOOPS_H
#define GAMELOOPS_H
#include <memory>
#include "player.h"
#include "humanPlayer.h"
#include "gameHandler.h"

/// @brief Loops di gioco che connettono le classi di input/output con GameHandler
namespace gameLoops{
    void game_loop(bool);
    void init_loop(const std::unique_ptr<Player> (&player)[2], GameHandler&, char (&playerInput)[6], bool);
    void main_loop(const std::unique_ptr<Player> (&player)[2], GameHandler&, char (&playerInput)[6], bool);
}

#endif
