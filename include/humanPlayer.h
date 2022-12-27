#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"
#include <iostream>
#include <cctype>

class HumanPlayer : public Player{
public:
    int get_input(char *) const override;
        //scrive su di un array di 6 char (2-3 char x coordinata)
        //ritorna codice reelativo al risultato dell' op (avvenuta, errori di sorta..) 
        //se sono presenti caratteri extra dopo il comando, li ignora
};

#endif