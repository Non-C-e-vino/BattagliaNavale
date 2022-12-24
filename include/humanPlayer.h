#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include <iostream>

class HumanPlayer : public Player{
public:
    Coord getInput() override;
};

#endif