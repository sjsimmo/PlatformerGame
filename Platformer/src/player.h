#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class player: public entity
{
private:
    char wall_collisions = 0;
    int airjumps_left = 0;
    int airjumps = 1;
public:
    void init(double _x_pos, double _y_pos);
    void update(double dt, const map &Map, const events &Events);
    void kill();
};

#endif