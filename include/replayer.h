#ifndef REPLAYER_H
#define REPLAYER_H
#include "player.h"

class Replayer : public Player{
public:
    int get_input(char *) const override; 
private:
    void read_log_input(char *);
};

#endif