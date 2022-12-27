#include "coord.h"
#include<cstring>

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

    //...

    return;
}

XY::XY(int x, int y) : xy{x,y} {};

bool XY::operator==(const XY&ref){
    if(this->xy[0] == ref.xy[0]  && this->xy[1] == ref.xy[1]) return true;
    return false;
}