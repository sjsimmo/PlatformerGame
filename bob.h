#ifndef BOB_H
#define BOB_H

#include "entity.h"

class bob: public entity
{
public:
    void init(double _x_pos, double _y_pos);
    void update(double dt, const map &Map, const events &Events);
    void kill();
};

#endif