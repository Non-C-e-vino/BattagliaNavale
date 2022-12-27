#ifndef GAMELOOPS_H
#define GAMELOOPS_H
#include <memory>
#include "player.h"
#include "humanPlayer.h"
#include "bot.h"
#include "replayer.h"
#include "gameHandler.h"

namespace gameLoops{
    void game_loop(bool);
    void replay_loop();
    void init_loop(const std::unique_ptr<Player> (&player)[2], GameHandler&);
    void main_loop(const std::unique_ptr<Player> (&player)[2], GameHandler&);
}

#endif
