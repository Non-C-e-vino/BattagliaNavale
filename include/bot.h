#ifndef BOT_H
#define BOT_H
#include "player.h"

class Bot : public Player{
public:
    int get_input(char *) const override;
    // ovviamente le gen va sepre a buon fine, return sempre = 0;
private: 
    // variabili tipo difficolta' in caso di ia non comp. randomica
    void gen_rand_coord(char *);
};

#endif