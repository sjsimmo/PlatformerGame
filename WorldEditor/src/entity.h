#ifndef ENTITY_H
#define ENTITY_H

#include "time_manager.h"

class map;

class entity
{
private:
    time_manager Time_manager;
    double old_x_pos, old_y_pos;
public:
    
    double x_pos, x_vel, x_acc;
    double y_pos, y_vel, y_acc;
    int width = 12, height = 24;
    int texture;
    void init();
    void move(double dt);
    char wall_collisions(map Map, bool collide); //call after move to see if collision occured
};

#endif