#ifndef LOGGER_H
#define LOGGER_H
#include <fstream>
#include <string>

namespace Log
{
    ///@brief Sovrascrive il file log
    void reset_log_file();
};

/// @brief Gestisce la lettura dei file di log
class InLogger{
public:
    InLogger(std::string&);

    InLogger(const InLogger&) = delete;
    InLogger operator=(const InLogger&) = delete;

    int read_log(char *inp);

    /**
     * @brief Legge il valore della moneta registrato su log
     * 
     * @warning da chiamare al posto del lancio della moneta
     * 
     * @return int coin
     */
    int read_coin_log();
    ~InLogger(){
        ifsptr->close(); 
        delete ifsptr;
    }
private:
    std::ifstream* ifsptr;
};

class OutLogger{
public:
    OutLogger(void);

    OutLogger(const OutLogger&) = delete;
    OutLogger operator=(const OutLogger&) = delete;

    ///@brief Registra coordinate in forma char su log file
    void log_cinput(char*);

    /**
     * @brief registra su log quale giocatore a iniziato
     * 
     * @warning da chiamare dopo aver lanciato la moneta, ma prima della fase di schieramento
     */
    void log_coin(int);

    ~OutLogger(){
        ofsptr->close(); 
        delete ofsptr;
    }
private:
    std::ofstream* ofsptr;
};

#endif
