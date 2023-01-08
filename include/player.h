#ifndef PLAYER_H
#define PLAYER_H
#include "coord.h"


/// @brief Interfaccia per le classi che gestiscono l'input
class Player{
public:
    /**
     * Formato output: scrive su di un array di 6 char, le coordinate
     * sono fornite senza spazi e se non raggiungono i 6 caratteri il
     * carattere termininatore è '\0'.
     * 
     * @return int 0 se il formato è corretto
     */
    virtual int get_ship_pos(char *) = 0;
    virtual int get_ship_act(char *) = 0;
    //forse (&char)[6] meglio? piu' leggibile
};

#endif