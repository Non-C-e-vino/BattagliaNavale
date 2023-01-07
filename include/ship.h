#ifndef SHIP_H
#define SHIP_H
#include "coord.h"

enum class Action{Fire, MoveAndRepair, MoveAndSearch};
enum class ShipType{Cor, NDS, Sot};

struct Hull;

class Ship{
public:
    virtual Action get_action() const = 0;

        //nota: chiamare le seguenti due funzioni significa modificare i punti vita della nave 
        //senza modificare lo stato dello scafo, il che porta ad errori logici
        //vengono automaticamente chiamate dai metodi dello scafo stesso, quindi non dovrebbero essere mai usate
        //Possibile soluzione: rendere Hull classe interna a Ship
    /**
     * @brief La barca perde un punto vita
     * @warning vedi nota in ship.h
     * 
     * @return true 
     * @return false se gli hp sono gia' a zero.
     */
    bool set_damage();
        /**
     * @brief La barca recupera un punto vita
     * @warning vedi nota in ship.h
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
    virtual bool is_core(Hull *) const = 0;
    virtual Hull* get_hull(int x) = 0; 
    virtual int get_size() const = 0; 
    bool is_sunk(){ return !hp; }
protected:
    int hp;
};

    struct Hull{
    public:
        Hull(){}
        Hull(Ship* owner, XY& c) : owner{owner}, c{c}{}
        Ship * getOwner(){ return owner; }
        bool is_hit() const { return !armor; }
        bool set_hit();
        XY get_c() const { return c; }
        void set_c(XY &c){ this->c = c; }
        bool heal();

    private:
        XY c; 
        bool armor = true;
        Ship * owner; 
    };

#endif