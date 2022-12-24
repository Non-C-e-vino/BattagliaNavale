#ifndef GAMELOOPS_H
#define GAMELOOPS_H
#include <memory>
#include "player.h"
#include "humanPlayer.h"
#include "bot.h"

namespace gameLoops{
    void initLoop(const std::unique_ptr<Player> &, const std::unique_ptr<Player> &);
    void mainLoop();
    void gameLoop(bool);
}

#endif
