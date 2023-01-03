#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

namespace Log{

void reset_log_file();
void log(char*);

};

class Logger{
public:
    Logger(std::string&);
    int read_log(char *inp);
    ~Logger(){
        ifsptr->close(); 
        delete ifsptr;
    }
private:
    std::ifstream* ifsptr;
};



#endif
