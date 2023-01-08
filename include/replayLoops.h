#ifndef GAMELOOPS_H
#define GAMELOOPS_H
#include <string>
#include <gameHandler.h>
#include <logger.h>

/// @brief Loops semplificati utili a mettere in atto le giocate estratte da Logger
namespace gameLoops{
    void replay_loop(std::string&, int delay = false);
    void replay_init_loop(Logger&, GameHandler&, char (&playerInput)[6], int delay = false);
    void replay_main_loop(Logger&, GameHandler&, char (&playerInput)[6], int delay = false);
}

#endif
