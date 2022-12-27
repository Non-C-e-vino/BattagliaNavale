#include "humanPlayer.h"
#include "gameHandler.h"
#include <cstring>

int HumanPlayer::get_input(char *inp){
    int i = 0;
    //bug: imposibile inserire coordinate con la lettera X (58+ caselle, sorvolabile)
    if(std::cin.peek() == 'X'){
        std::cin.read(inp, 5);
        if(!std::cin.eof()) std::cin.ignore(264, '\n');
        if(!std::strcmp(inp, "XX XX")) {
            inp[5] = '\0';
            return 0;
        }
        else return -1;
    }
    
    while(i <= 5){
        if(std::cin.peek() > 'A' && std::cin.peek() < 'Z') 
            std::cin.get(inp[i]);
        else{
            std::cin.ignore(264, '\n');
            return -1;
        }
        ++i;
        if(std::isdigit(std::cin.peek())) 
            std::cin.get(inp[i]);
        else{
            std::cin.ignore(264, '\n');
            return -2;
        }
        ++i;
        if(std::isdigit(std::cin.peek())){
            std::cin.get(inp[i]);
            ++i;
        }
        else if(i >= 4) break;
        else if(std::cin.peek() == ' ') std::cin.ignore(1);
        else{
            std::cin.ignore(264, '\n');
            return -3;
        }
        while(std::cin.peek() == ' ') std::cin.ignore(1);
    }
    
    std::cin.ignore(264, '\n');
    if(i < 6) inp[i] = '\0';
    return 0;
}