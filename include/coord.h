#ifndef COORD_H
#define COORD_H

enum Rotation{ vert, oriz };

struct XY{
    XY(int x = 0, int y = 0);
    int xy[2]; 
    bool operator==(const XY&) const;
    bool operator!=(const XY&) const;
    bool operator<(const XY&) const;
    XY operator+=(const XY&);
};
XY operator-(const XY&, const XY&);
XY operator+(const XY&, const XY&);
/// @brief Genera una coppia di coordinate da un array di char
void char_to_coord(XY (&xy)[2], char (&inp)[6]);
/// @brief Genera un array di char da una coppia di coordinate
void coord_to_char(XY (&xy)[2], char* inp);
/// @brief Con
/// @param  
/// @return 
bool check_c_oob(const XY &); //out of bounds
void print_char_coord(char* playerInput);

#endif
