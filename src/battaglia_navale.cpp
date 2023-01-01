#include <iostream>
#include <cstring>
#include "gameLoops.h"

void argsError();

int main(int argc, char *argv[]){
    
    XY offset = XY{3,3} - XY{6,6};

    std::cout << offset.xy[0] << "  " << offset.xy[1] <<"\n";

    GameHandler g{}; 
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
    std::cout << "Fornire un argomento valido:\n\t[pc]: player vs computer\n\t[cc]: computer vs computer\n";
}