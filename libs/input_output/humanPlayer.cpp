/**
 * 
 * @author Demo Filippo
 * 
 */

#include "humanPlayer.h"
#include <iostream>
#include <cstring>
#include <cctype>

int HumanPlayer::get_ship_pos(char *inp){
    return get_input(inp);
}

int HumanPlayer::get_ship_act(char *inp){
    return get_input(inp);
}

int HumanPlayer::get_input(char *inp){

    //Conta le lettere inserite
    int i = 0;

    //I caratteri X Y Z sono riservati per i comandi speciali
    if(std::cin.peek() == 'X' || std::cin.peek() == 'Y' || std::cin.peek() == 'Z')
    {
        std::cin.get(inp, 6);

        std::cin.ignore(264, '\n');

        if(!(std::strcmp(inp, "XX XX") && std::strcmp(inp, "YY YY") && std::strcmp(inp, "ZZ ZZ")))
            return 0;

        return -4;
    }
    
    //Controllo la presenza di una coppia valida di coordinate  
    do{
        if(std::cin.peek() >= 'A' && std::cin.peek() < 'X')
        {
            std::cin.get(inp[i]);
            ++i;
        }
        else
        {
            std::cin.ignore(264, '\n');
            return -1;
        }

        if(std::isdigit(std::cin.peek()))
        {
            std::cin.get(inp[i]);
            ++i;
        }
        else
        {
            std::cin.ignore(264, '\n');
            return -2;
        }
        
        if(std::isdigit(std::cin.peek()))
        {
            std::cin.get(inp[i]);
            ++i;
        }
        else
        {
            if(i >= 4) 
                break;
            else 
                if(std::cin.peek() == ' ')
                    std::cin.ignore(1);
                else
                {
                    std::cin.ignore(264, '\n');
                    return -3;
                }
        }
    }while(i < 4);
    
    std::cin.ignore(264, '\n');
    if(i < 6) inp[i] = '\0';
    return 0;
}