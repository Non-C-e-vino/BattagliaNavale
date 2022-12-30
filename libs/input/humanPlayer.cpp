#include "humanPlayer.h"
#include "gameHandler.h"
#include <cstring>

int HumanPlayer::get_ship_pos(char *inp){
    return get_input(inp);
}

int HumanPlayer::get_ship_act(char *inp){
    return get_input(inp);
}

int HumanPlayer::get_input(char *inp){
    int i = 0;
    //bug: imposibile inserire coordinate con la lettera X (58+ caselle, sorvolabile)
    if(std::cin.peek() == 'X' || std::cin.peek() == 'Y' || std::cin.peek() == 'Z'){
        std::cin.read(inp, 5);
        inp[5] = '\0';
        if(!std::cin.eof()) std::cin.ignore(264, '\n');
        if(!(std::strcmp(inp, "XX XX") && std::strcmp(inp, "YY YY") && std::strcmp(inp, "ZZ ZZ"))) return 0;
        return -4;
    }
    do{
        if(std::cin.peek() >= 'A' && std::cin.peek() < 'X'){
            std::cin.get(inp[i]);
            ++i;
        }else{
            std::cin.ignore(264, '\n');
            return -1;
        }
        if(std::isdigit(std::cin.peek())){
            std::cin.get(inp[i]);
            ++i;
        }else{
            std::cin.ignore(264, '\n');
            return -2;
        }
        
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
    }while(i < 4);
    
    std::cin.ignore(264, '\n');
    if(i < 6) inp[i] = '\0';
    return 0;
}