#ifndef GAMELOOPS_H
#define GAMELOOPS_H
#include <string>
#include <gameHandler.h>
#include <logger.h>

namespace gameLoops{
    void replay_loop(std::string&, int delay = false);
    void replay_init_loop(Logger&, GameHandler&, char (&playerInput)[6], int delay = false);
    void replay_main_loop(Logger&, GameHandler&, char (&playerInput)[6], int delay = false);
}

#endif
