#ifndef GAMEHANDLER_H
#define GAMEHAMDLER_H
#include <memory>
#include <vector>
#include "admiral.h"
#include "gameVars.h"
#include "player.h"

/*! \mainpage Pagina principale
 *
 * \section imp_sec Note di implementazione
 *
 * testtesttest
 *
 * \section err_sec Problemi
 *
 * \subsection ott_sec di ottimizzazione
 * testtesttest
 * 
 * \subsection des_sec di design
 * testtesttest
 *
 * \subsection leg_sec di leggibilita'
 * testtesttest
 */

/// @brief Gestisce tutto cio' che concerne le meccaniche di gioco
class GameHandler{
public:
    void display_grids(Admirals) const;
    void clear_att_grid(Admirals);
    void clear_sonar(Admirals);

    /**
     * @brief Genera una nave, la assegna ad un ammiraglio e la posiziona sulla griglia di quest'ultimo.
     * 
     * @param adm 
     * @param st Tipo della nave. Vedi Admirals
     * @param xy Le coordinate di inizio e fine della nave
     * @return int 0 se l'operazione è andata a buon fine
     */
    int set_ship(Admirals adm, ShipType st, XY (&xy)[2]);

    /**
     * @brief Se possibile, svolge l'azione richiesta
     * 
     * @param adm 
     * @param xy Le coordinate del core della nave di cui attivare l'azione e quelle del bersaglio di tale azione
     * @return int 0 se l'operazione è andata a buon fine 
     */
    int ship_action(Admirals adm, XY (&xy)[2]);

    /**
     * @brief Riempie il vettore membro cores con i riferimenti a tutti i core delle navi in gioco.
     * Necessario al funzionamento dei Bot, da chiamare tra la fase di schieramento e quella di combattimento
     */
    void set_cores();

    /**
     * @brief Ritorna un riferimento al core situato al dato indice
     * 
     * @param i 
     * @return Hull* 
     */

    /**
     * @brief Aumenta il contatore turn
     * 
     * @return true 
     * @return false se eccede MAXTURNS
     */
    bool next_turn();

    /**
     * @brief
     * 
     * @param adm 
     * @return true se l'ammiraglio passato ha vinto
     * @return false 
     */
    bool is_winner(Admirals adm);
    int get_turn(){ return turn; }

    /**
     * @brief inizializza coin a 0 o a 1
     * @warning da chiamare dopo std::srand(mySeed)
     */
    void flip_coin();

    int get_coin(){ return coin; }

    //necessario per i replay
    int set_coin(int c){ coin = c; return coin; }

    int get_active_ships_n(Admirals adm){ return admiral[(int)adm].shipC; }

    /**
     * @brief Cerca eventuali navi affondate appartenenti al dato ammiraglio e provvede
     *  ad eliminarle dalla mappa, dalla memoria e dal vettore di core attivi.
     */
    void remove_all_sunk(Admirals);

    /**
     * @brief giocatore automatico che effettua mosse casuali ogni turno
     * @warning prima di utilizzare i metodi di questa classe,
     * assicurarsi di aver chiamato almeno una volta std::srand(mySeed)
     */
    class Bot : public Player {
    public:
        Bot(GameHandler*);
        int get_ship_pos(char *) override;
        int get_ship_act(char *) override;
        // ovviamente le gen va sempre a buon fine, return sempre = 0;
    private: 
        GameHandler* gh;
        void gen_rand_coord(XY (&xy)[2]) const;
        void gen_rand_ship_coord(XY (&xy)[2]) const;
        // variabili tipo difficolta' in caso di ia non comp. randomica
    };

private:
    int turn = 0;
    int coin ;
    Admiral admiral[2];
    std::vector<Hull*> cores;

    Hull* get_core(int i);

    /**
     * @brief Genera un array di posizioni sulla griglia che una barca
     *  delle dimensioni specificate possa occupare. Parte di set_ship()
     * 
     * @param shipC output
     * @param xy input, coordinate inizio e fine nave
     * @param size dimensione nave
     * @return int 0 se l'output è stato generato correttamente
     */
    int gen_ship_c(XY* shipC, XY (&xy)[2], int size, Admirals) const;

    /**
     * @brief Posiziona la data barca sulla griglia di difesa del dato ammiraglio.
     * 
     * @param ship 
     * @param adm 
     */
    void set_ship_on_map(std::unique_ptr<Ship>& ship, Admirals adm);

    /**
     * @brief Posiziona la data barca sulla griglia di difesa del dato ammiraglio.
     * 
     * @param ship 
     * @param adm 
     */

    void set_ship_on_map(Ship* ship, Admirals adm);

    /**
     * @brief Rimuove la data barca dalla griglia di difesa del dato ammiraglio.
     * 
     * @param ship 
     * @param adm 
     */
    void detach_ship_from_map(Ship* ship, Admirals adm);

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