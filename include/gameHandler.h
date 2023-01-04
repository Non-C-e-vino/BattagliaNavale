#ifndef GAMEHANDLER_H
#define GAMEHAMDLER_H
#include <memory>
#include <vector>
#include "admiral.h"
#include "gameVars.h"

class GameHandler{
public:
    void display_grids(Admirals) const;
    void clear_att_grid(Admirals);

    //rimuove di simobli di mancato bersaglio e del sonar contemporaneamente dalla griglia d'attacco del chiamante
    void clear_miss_sonar(Admirals);

    //date le coordinate di inizio e fine di una nave, genera un oggetto del relativo tipo
    //e lo assegna al relativo ammiraglio, subito prima di aver posizionato la barca sulla griglia di difesa dello stesso
    //ritorna 0 se l'operazione e' riuscita
    int set_ship(Admirals, ShipType, XY (&xy)[2]);

    //riceve le coordinate del core della nave di cui attivare l'azione e quelle del bersaglio di tale azione
    //se possibile, svolge tale azione
    //ritorna 0 se l'operazione e' riuscita
    int ship_action(Admirals, XY (&xy)[2]);

    //riempie il vettore membro cores con i riferimenti a tutti i core delle navi in gioco
    //necessario al funzionamento del bot, da chiamare tra la fase di schieramento e quella di combattimento
    void set_cores();

    //ritorna un riferimento al core situato al dato indice
    Hull* get_core(int);

    //aumenta il contatore turn, ritorna false se eccede MAXTURNS
    bool next_turn();

    //true se l'ammiraglio passato ha vinto
    bool is_winner(Admirals adm);
    int get_turn(){ return turn; }

    //inizializza coin a 0 o a 1
    void flip_coin();
    int get_coin(){ return coin; }

    //necessario per i replay
    int set_coin(int c){ coin = c; return coin; }
    int get_active_ships_n(Admirals adm){ return admiral[(int)adm].shipC; }

    //cerca eventuali navi affondate appartenenti al dato ammiraglio e provvede ad eliminarle
    //dalla mappa, dalla memoria e dal vettore di core attivi
    void remove_all_sunk(Admirals);
private:
    int turn = 0;
    int coin ;
    Admiral admiral[2];
    std::vector<Hull*> cores;

    //dati tipo e coordinate di inizio e fine di una barca, genera l'array di coordinate che
    //tale barca occuperà. E' parte di set_ship
    //ritorna 0 se l'operazione e' riuscita
    int gen_ship_c(XY *, XY (&xy)[2], int, Admirals) const;

    //posiziona la data barca sulla griglia di difesa del dato ammiraglio
    void set_ship_on_map(std::unique_ptr<Ship>& , Admirals);
    void set_ship_on_map(Ship*, Admirals);

    //come sopra ma effetto opposto
    void detach_ship_from_map(Ship*, Admirals);

    //i metodi successivi sono le parti di ship_action 
    //responsabili dello svoglimento delle azioni
    int action_fire(XY&, Admirals);
    int action_move_heal(Hull*, XY&, Admirals);
    int action_move_search(Hull*, XY&, Admirals);
    bool move_ship(Hull*, XY&, Admirals);
    void heal_aoe(Hull*, Admirals);
    void ricognizione(XY&, Admirals);
};

#endif