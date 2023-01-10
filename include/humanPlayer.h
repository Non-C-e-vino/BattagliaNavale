#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H
#include "player.h"

/// @brief Gestisce l'input da terminale
class HumanPlayer : public Player{
public:
    int get_ship_pos(char *) override;
    int get_ship_act(char *) override;
private: 
    //scrive su di un array di 6 char (2-3 char x coordinata)
    //ritorna codice relativo al risultato dell' op (avvenuta, errori di sorta..) 
    //NOTA: se sono presenti caratteri extra dopo il comando, li ignora
    int get_input(char *);     
};

#endif