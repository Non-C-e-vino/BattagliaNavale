#include<iostream>
#include"gameLoops.h"
#include<cstring>

void argsError();

int main(int argc, char *argv[]){
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
    gameLoops::gameLoop(pc);
    return 0;
}

void argsError(){
    std::cout << "Fornire un argomento valido:\n\t[pc]: player vs computer\n\t[cc]: computer vs computer\n";
}