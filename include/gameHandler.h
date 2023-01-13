#ifndef GAMEHANDLER_H
#define GAMEHAMDLER_H
#include <memory>
#include <vector>
#include <set>
#include "admiral.h"
#include "gameVars.h"
#include "player.h"

/// @brief Gestisce tutto cio' che concerne le meccaniche di gioco
class GameHandler{
public:
    GameHandler();
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
     * @brief Giocatore automatico che effettua mosse casuali ogni turno.
     */
    class Bot : public Player {
    public:
        Bot(GameHandler*);
        int get_ship_pos(char *) override;
        int get_ship_act(char *) override;
        // ovviamente le gen va sempre a buon fine, return sempre = 0;
    protected: 
        GameHandler* gh;
         void gen_rand_coord(XY (&xy)[2]) const;
        void gen_rand_ship_coord(XY (&xy)[2]) const;
        // variabili tipo difficolta' in caso di ia non comp. randomica
    };
    /**
     * @brief Bozza di bot intelligente, ha un comportamento ancora simile a Bot,
     * con la differenza che le corazzate sparano solo su bersagli rilevati dal sonar, se presenti.
     */ 

    class CleverBot : public Bot {
    public:
        CleverBot(GameHandler*);
    private:
        int get_ship_act(char *) override;
        void gen_clever_coord(XY (&xy)[2]);
        std::set<XY> targets;
        bool shootingTime = false;
        bool hasScanned = true;
        //bool scanners = RICO; //  WIP
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

//TODO: metodo Admiral getCurrentPlayer() in GameHandler
// sostituire dove viene ricavato per esteso (GameLoops, Bot, ..)



/*! \mainpage Note di implementazione
 *
 * \section imp_sec 
 *
 * testtesttest
 *
 * \subsection ott_sec Ottimizzazione
 * Inizialemente il file di log veniva aperto e chiuso ad ogni turno,
 * ma e' evidente (grazie al profiler di VS) che questo sia molto inefficiente soprattutto
 * se si registrano lunghe partite tra Bot, quindi i file rimangono sempre aperti 
 * durante l'esecuzione (grazie a InLogger e OutLogger).
 * I messaggi su terminale vengono minimizzati in caso di partite tra bot.
 * 
 * \subsection des_sec Problemi strutturali
 * L'idea iniziale era di mentanere separate le classi generatrici di input (che implementano Player) e il GameHandler.
 * e' pero' diventato sempre piu' evidente che il giocatore computer (Bot) deve accedere
 * a informazioni di GameHandler che che vanno al di la' dell'incapsulamento di quest'ultimo,
 * quindi Bot e' stata resa sua classe interna. Per quanto questa soluzione possa avere un senso logico,
 * sarebbe sicuramente piu' pratico se GameHandler potesse simulare la giocata di Bot, 
 * senza che quest'ultimo generi effettivamente delle coordinate in forma testuale
 * che vanno poi riconvertite, passando per i loop di gioco. E' anche vero che a quel punto
 * nascerebbe il problema del log, che andrebbe gestito in altro modo.
 * Anche Hull sarebbe dovuta diventare interna a Ship, ma, sinceramente, non mi e' ancora chiaro se
 * una classe virtuale pura puo' avere in se' classi interne non virtuali pure. Sono quindi
 * pubblichi dei metodi che sarebbe meglio non lo fossero ( Ship::set_damage(), Ship::heal() ).
 *
 * \subsection leg_sec Problemi di leggibilita'
 * L'uso delle convenzioni per i nomi poteva essere migliore (es. distinguere dati
 * membro con la notazione m_datoMembro) .
 * Gli oggetti di classe XY non vengono dichiarati sempre sotto lo stesso nome 
 * (ad es. "c", "ref", "xy"), e la scrittura risulta ambigua in quanto quando si 
 * accede al membro xy[2] si scrive spesso xy[indiceOggettoXY].xy[IndiceArrayMembro] .
 */
