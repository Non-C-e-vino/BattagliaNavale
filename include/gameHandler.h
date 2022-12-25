#ifndef GAMEHANDLER_H
#define GAMEHAMDLER_H
#include "coord.h"
#include "ship.h"

enum Admirals{ BlueAdm, RedAdm };

class GameHandler{
public:
    void diplay_grid(Admirals) const;
    void clear_grid(Admirals);
    int set_ship(Admirals, Coord, Coord); //da valutare se coord, rotation
    int move_ship(Admirals, Coord, Coord);
    int action_ship(Admirals, Coord, Coord);
private:
    struct Admiral{
        Ship* ships;
    };
    int turn = 0;
    Admiral admirals[2];
};

#endif