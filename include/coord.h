#ifndef COORD_H
#define COORD_H

enum Rotation{ vert, oriz };

struct XY{
    XY(int x = 0, int y = 0);
    int xy[2]; 
    bool operator==(const XY&) const;
    bool operator!=(const XY&) const;
    XY operator+=(const XY&);
};
XY operator-(const XY&, const XY&);
XY operator+(const XY&, const XY&);
void coord_convert(XY (&xy)[2], char (&inp)[6]);
void coord_to_char(XY (&xy)[2], char* inp);
bool check_c_oob(const XY &); //out of bounds

#endif
