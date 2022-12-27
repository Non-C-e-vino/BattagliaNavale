#ifndef COORD_H
#define COORD_H

enum Rotation{ vert, oriz };

struct XY{
    int xy[2]; 
};

void coord_convert(XY (&xy)[2], char (&inp)[6]);

#endif
