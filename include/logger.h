#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

namespace Log{

void reset_log_file();
void log_cinput(char*);
void log_coin(int);

};

class Logger{
public:
    Logger(std::string&);
    int read_log(char *inp);
    int read_coin_log();
    ~Logger(){
        ifsptr->close(); 
        delete ifsptr;
    }
private:
    std::ifstream* ifsptr;
};



#endif
