#ifndef REPLAYER_H
#define REPLAYER_H
#include "player.h"

class Replayer : public Player{
public:
    int get_ship_pos(char *) override;
    int get_ship_act(char *) override;
private: 
    int get_input(char *) override;
    void read_log_input(char *);
};

#endif