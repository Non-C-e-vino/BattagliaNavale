/*
 * 
 * @author Salese Alberto
 * 
 */

#ifndef SHIP_H
#define SHIP_H
#include "coord.h"

enum class ShipAction{Fire, MoveAndRepair, MoveAndSearch};
enum class ShipType{Cor, NDS, Sot};

struct Hull;

class Ship{
public:
    virtual ShipAction get_action() const = 0;

        //nota: chiamare le seguenti due funzioni significa modificare i punti vita della nave 
        //senza modificare lo stato dello scafo, il che porta ad errori logici
        //vengono automaticamente chiamate dai metodi dello scafo stesso, quindi non dovrebbero essere mai usate
        //Possibile soluzione: rendere Hull classe interna a Ship
    /**
     * @brief La barca perde un punto vita
     * @warning Sconsigliato l'utilizzo. Vedi nota in ship.h
     * 
     * @return true 
     * @return false se gli hp sono gia' a zero.
     */
    bool set_damage();
        /**
     * @brief La barca recupera un punto vita
     * @warning Sconsigliato l'utilizzo. Vedi nota in ship.h
     * 
     * @return true 
     * @return false se gli hp sono gia' al massimo.
     * 
     */  
    virtual bool heal() = 0;    

    //questa f chiama a sua volta i metodi dello scafo, quindi si puo' usare liberamente

    /**
     * @brief Chiama Hull::heal() su tutti i pezzi di scafo della nave
     * 
     * @return true 
     * @return false se Ship::heal() ritorna false
     */
    virtual bool full_heal() = 0;

    /**
     * @brief Il core e' la parte centrale dello scafo
     * 
     * @param ref
     * @return true se ref punta al core della nave
     * @return false 
     */
    virtual bool is_core(Hull* ref) const = 0;
    virtual Hull* get_hull(int x) = 0; 
    virtual int get_size() const = 0; 
    bool is_sunk(){ return !hp; }
protected:
    int hp;
};

/// @brief  Lo scafo o parde dello scafo di una nave
struct Hull
{
public:
    Hull(){}
    Hull(Ship* owner, XY& c) : owner{owner}, c{c}{}
    Ship * getOwner(){ return owner; }
    bool is_hit() const { return !armor; }
    bool set_hit();
    bool heal();
    XY get_c() const { return c; }
    void set_c(XY &c){ this->c = c; }
private:
    XY c; 
    bool armor = true;
    Ship * owner; 
};

#endif