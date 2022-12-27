#ifndef COORD_H
#define COORD_H

enum Rotation{ vert, oriz };

struct XY{
    XY(int x = 0, int y = 0);
    int xy[2]; 
    bool operator==(const XY &);
};

void coord_convert(XY (&xy)[2], char (&inp)[6]);

#endif
