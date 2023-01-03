#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

namespace Log{

//sovrascrive il file log
void reset_log_file();

//in output il file viene aperto e chiuso ad ogni lettura
//non dovrebbe essere un problema in quanto non ci si aspetta
//che ottimizzare la velocita' dei turni sia importante in un gioco
//strategico di questo tipo

//si sarebbero potute salvare le coordinate gia' convertite ma, 
//essendo che la consegna richiede una forma testuale,
//non avrebbe avuto senso pratico

//registra le coordinate su file log
void log_cinput(char*);

//da chiamare dopo aver lanciato la moneta, ma prima della fase di schieramento
//serve a sapere quale giocatore a iniziato
void log_coin(int);

};
//d'altro canto ottimizzare la lettura velocità
//di trascrizione può avere senso
class Logger{
public:
    Logger(std::string&);

    Logger(const Logger&) = delete;
    Logger operator=(const Logger&) = delete;

    int read_log(char *inp);

    //da chiamare al posto del lancio della moneta
    int read_coin_log();
    ~Logger(){
        ifsptr->close(); 
        delete ifsptr;
    }
private:
    std::ifstream* ifsptr;
};



#endif
