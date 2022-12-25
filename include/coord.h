#ifndef COORD_H
#define COORD_H

enum Rotation{ vert, oriz };

struct Coord{
    int xy[2]; 
};

Coord coord_convert(char, char);

#endif
