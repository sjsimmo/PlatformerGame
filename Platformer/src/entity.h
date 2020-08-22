#ifndef ENTITY_H
#define ENTITY_H

#include "time_manager.h"

class map;
class events;

class entity
{
private:
    time_manager Time_manager;
    double old_x_pos, old_y_pos;
public:
    virtual void init(double _x_pos, double _y_pos){};
    virtual void update(double dt, const map &Map, const events &Events){};
    virtual void kill(){};

    double x_pos, x_vel, x_acc;
    double y_pos, y_vel, y_acc;
    int width = 12, height = 24;
    int texture;
    void entity_init();
    void entity_move(double dt);
    char entity_wall_collisions(const map &Map, bool collide); //call after move to see if collision occured
};

#endif