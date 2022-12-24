#ifndef BOT_H
#define BOT_H
#include "player.h"

class Bot : public Player{
public:
    Coord getInput() override;
};

#endif