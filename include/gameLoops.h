#ifndef GAMELOOPS_H
#define GAMELOOPS_H
#include <memory>
#include "player.h"
#include "humanPlayer.h"
#include "bot.h"
#include "gameHandler.h"

namespace gameLoops{
    void init_loop(const std::unique_ptr<Player> &, const std::unique_ptr<Player> &, GameHandler&);
    void main_loop(const std::unique_ptr<Player> &, const std::unique_ptr<Player> &, GameHandler&);
    void game_loop(bool);
}

#endif
