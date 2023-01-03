#ifndef REPLAYER_H
#define REPLAYER_H
#include "player.h"
#include "logger.h"

class Replayer : public Player{
public:
    int get_ship_pos(char *) override;
    int get_ship_act(char *) override;
private:
    Logger l;
};

#endif