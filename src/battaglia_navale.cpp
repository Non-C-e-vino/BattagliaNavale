#include <iostream>
#include <cstring>
#include <fstream>
#include "gameLoops.h"

void argsError();

int main(int argc, char *argv[]){

    if(SHIPSN%2){
        std::cout << "Il numero totale delle navi in gioco deve essere pari.";
        return 0;
    }
     
    bool pc;

    if(argc != 2){
        argsError();
        return 0;
    }else if(!strcmp(argv[1], "cc")|| !strcmp(argv[1], "CC")){
        pc = false;
    }else if(!strcmp(argv[1], "pc") || !strcmp(argv[1], "PC")){
        pc = true;
    }else{
        argsError();
        return 0;
    }
    gameLoops::game_loop(pc);
    return 0;
}

void argsError(){
    std::cout << "Fornire un argomento valido:\n\t"
    << "argomento \"pc\": player vs computer\n\t"
    << "argomento \"cc\": computer vs computer\n" << std::endl;
}