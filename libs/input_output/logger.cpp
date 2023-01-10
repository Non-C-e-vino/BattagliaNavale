#include "logger.h"
#include "gameVars.h"
#include <fstream>
#include <iostream>
#include <memory>
#include <cctype>

InLogger::InLogger(std::string& fileName){
    std::unique_ptr<std::ifstream> ifs= std::make_unique<std::ifstream>(fileName);
    if(!ifs->is_open()) throw std::runtime_error("Impossibile aprire il log file.");
    ifsptr = ifs.release();
}

int InLogger::read_log(char *inp){
    if(ifsptr->is_open()){
        if(!std::isalpha((*ifsptr).peek())) return -1;
        int i = 0;
        for(; (*ifsptr).peek() != '-'; ++i)
            (*ifsptr).get(inp[i]);
        (*ifsptr).ignore(1);
        if(i < 6) inp[i] = '\0';
        return 0;
    }
    else throw std::runtime_error("Impossibile aprire il log file.");
}

int InLogger::read_coin_log(){
    if(ifsptr->is_open()){
        if(!std::isdigit((*ifsptr).peek())) return -1;
        int i;
        (*ifsptr) >> i;
        return i;
    }
    else throw std::runtime_error("Impossibile aprire il log file.");
}

void Log::reset_log_file()
{
    std::ofstream ofs;
    ofs.open(LOGFILE, std::ios::trunc);
    if(!ofs.is_open())
        throw std::runtime_error("Impossibile creare il log file.");
    ofs.close(); //anche se non servirebbe uscendo dallo scope
}

OutLogger::OutLogger(void){
    std::unique_ptr<std::ofstream> ofs= std::make_unique<std::ofstream>();
    ofs->open(LOGFILE, std::ios::app);
    if(!ofs->is_open()) throw std::runtime_error("Impossibile aprire il log file.");
    ofsptr = ofs.release();
}

void OutLogger::log_cinput(char* inp)
{
    if(ofsptr->is_open()){
        int i = 3;
        while(i < 6 && inp[i] != '\0') ++i;
        (*ofsptr).write(inp, i);
        (*ofsptr) << '-';
    }
    else throw std::runtime_error("Impossibile aprire il log file.");
}

void OutLogger::log_coin(int coin)
{
    if(ofsptr->is_open()){
        (*ofsptr) << coin;
    }
    else throw std::runtime_error("Impossibile aprire il log file.");
}
