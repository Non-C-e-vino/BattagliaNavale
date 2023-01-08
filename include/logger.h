#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

namespace Log{

///@brief Sovrascrive il file log
void reset_log_file();

//in output il file viene aperto e chiuso ad ogni lettura
//non dovrebbe essere un problema in quanto non ci si aspetta
//che ottimizzare la velocita' dei turni sia importante in un gioco
//strategico di questo tipo

//si sarebbero potute salvare le coordinate gia' convertite ma, 
//essendo che la consegna richiede una forma testuale,
//non avrebbe avuto senso pratico

///@brief registra le coordinate su file log
void log_cinput(char*);

/**
 * @brief registra su log quale giocatore a iniziato
 * 
 * @warning da chiamare dopo aver lanciato la moneta, ma prima della fase di schieramento
 */
void log_coin(int);

};
//d'altro canto ottimizzare la lettura velocità
//di trascrizione può avere senso

/// @brief Gestisce la lettura dei file di log
class Logger{
public:
    Logger(std::string&);

    Logger(const Logger&) = delete;
    Logger operator=(const Logger&) = delete;

    int read_log(char *inp);

    /**
     * @brief Legge il valore della moneta registrato su log
     * 
     * @warning da chiamare al posto del lancio della moneta
     * 
     * @return int coin
     */
    int read_coin_log();
    ~Logger(){
        ifsptr->close(); 
        delete ifsptr;
    }
private:
    std::ifstream* ifsptr;
};



#endif
