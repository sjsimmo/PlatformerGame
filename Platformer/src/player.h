#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"

class player: public entity
{
private:
    //Physics Tuning Parameters
    double walk_acc = 800;
    double walk_vel = 150;
    double air_acc = 250;
    double jump_vel = 180;
    int airjumps = 1;
    double airjump_vel = 150;
    double walljump_vel = 160;
    double walljump_x_vel = 150;
    double endjump_acc = 1300;
    double wallslide_vel = 100;
    double gravity = 300;

    char wall_collisions = 0;
    int airjumps_left = 0;
    int jump_was_pressed = false;
public:
    void init(double _x_pos, double _y_pos);
    void update(double dt, const map &Map, const events &Events);
    void kill();
};

#endif