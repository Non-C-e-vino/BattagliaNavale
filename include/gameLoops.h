#ifndef GAMELOOPS_H
#define GAMELOOPS_H
#include <memory>
#include <string>
#include "player.h"
#include "humanPlayer.h"
#include "bot.h"
#include "replayer.h"

namespace gameLoops{
    void game_loop(bool);
    void replay_loop(std::string&, bool delay = false);
    void init_loop(const std::unique_ptr<Player> (&player)[2], GameHandler&, char (&playerInput)[6]);
    void main_loop(const std::unique_ptr<Player> (&player)[2], GameHandler&, char (&playerInput)[6]);
    void replay_init_loop(Logger&, GameHandler&, char (&playerInput)[6], bool delay = false);
    void replay_main_loop(Logger&, GameHandler&, char (&playerInput)[6], bool delay = false);
}

#endif
