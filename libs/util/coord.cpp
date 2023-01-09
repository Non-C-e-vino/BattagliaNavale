#include "coord.h"
#include "gameVars.h"
#include <cctype>
#include <iostream>

void coord_convert(XY (&xy)[2], char (&inp)[6]){

    if(inp[0] == 'X'){      //non serve confrontare tutta la stringa, sono caratteri riservati
        xy[0] = XY{-1,-1};
        return;
    }
    if(inp[0]== 'Y'){
        xy[0] = XY{-2,-2};
        return;
    }    
    if(inp[0] == 'Z'){
        xy[0] = XY{-3,-3};
        return;
    }

    for(int i = 0, c = 0; i < 6 && inp[i] != '\0'; c++){
        xy[c].xy[0] = (int)(inp[i] - 'A');
        ++i;
        if(std::isdigit(inp[i+1])){
            xy[c].xy[1] += ((int)(inp[i] - '0')*10);
            ++i;
        }
        xy[c].xy[1] += (int)(inp[i] - '1');
        ++i;
    }
    return;
}

void coord_to_char(XY (&xy)[2], char *inp){

    int i = 0;
    for(int c = 0; c < 2; c++){
        inp[i] = (char)('A' + xy[c].xy[0]);
        ++i;
        if(xy[c].xy[1]+1 > 9){
            inp[i] = (char)('0' + (xy[c].xy[1] + 1)/10);
            ++i;
        }
        inp[i] = (char)('0' + (xy[c].xy[1] + 1)%10);
        ++i;
    }
    if(i < 6) inp [i] = '\0';
    //std::cout << inp;
    return;
}

XY::XY(int x, int y) : xy{x,y} {};

bool XY::operator==(const XY&ref) const {
    if(this->xy[0] == ref.xy[0]  && this->xy[1] == ref.xy[1]) return true;
    return false;
}

bool XY::operator<(const XY&ref) const {
    if(this->xy[0] < ref.xy[0]) return true;
    else if(this->xy[0] > ref.xy[0]) return false;
    else if(this->xy[1] < ref.xy[1]) return true;
    else return false;
}

bool XY::operator!=(const XY& ref) const {
    if(*this == ref) return false;
    return true;
}

XY XY::operator+=(const XY& ref){
    xy[0] += ref.xy[0];
    xy[1] += ref.xy[1];
    return *this;
}

XY operator-(const XY& c1, const XY& c2){
    return XY{c1.xy[0]-c2.xy[0], c1.xy[1]-c2.xy[1]};   
}

XY operator+(const XY& c1, const XY& c2){
    return XY {c1.xy[0]+c2.xy[0], c1.xy[1]+c2.xy[1]};
}

bool check_c_oob(const XY& c) {
    if(c.xy[0] >= 0 && c.xy[0] < GRIDSIZE && c.xy[1] >= 0 && c.xy[1] < GRIDSIZE) return false;
    return true;
}

void print_char_coord(char* playerInput){
    std::cout << playerInput[0];
    for(int i = 1; i < 6 && playerInput[i] != '\0'; ++i){
        if(std::isalpha(playerInput[i])) std::cout << ' ';
        std::cout << playerInput[i];
    }
}