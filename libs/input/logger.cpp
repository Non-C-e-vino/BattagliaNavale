#include "logger.h"
#include "gameVars.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <cctype>

Logger::Logger(std::string& fileName){
    std::unique_ptr<std::ifstream> ifs= std::make_unique<std::ifstream>(fileName);
    if(!ifs->is_open()) throw std::runtime_error("Impossibile aprire il log file.");
    ifsptr = ifs.release();
}

int Logger::read_log(char *inp){
    if(!std::isalpha(ifsptr->peek())) return -1;
    if(ifsptr->is_open()){
        int i = 0;
        for(; ifsptr->peek() != '-'; ++i)
            ifsptr->get(inp[i]);
        ifsptr->ignore(1);
        if(i < 6) inp[i] = '\0';
    }
    else throw std::runtime_error("Impossibile aprire il log file.");
    return 0;
}

void Log::reset_log_file()
{
    std::ofstream ofs;
    ofs.open(LOGFILE, std::ios::trunc);
    if(!ofs.is_open())
        throw std::runtime_error("Impossibile creare il log file.");
    ofs.close(); //anche se non servirebbe uscendo dallo scope
}

void Log::log(char* inp)
{
    std::ofstream ofs;
    ofs.open(LOGFILE, std::ios::app);
    if(ofs.is_open()){
        for(int i = 0; i < 6 && inp[i] != '\0'; ++i) 
            ofs << inp[i];
        ofs << '-';
    }
    else throw std::runtime_error("Impossibile aprire il log file.");
    ofs.close();
}
