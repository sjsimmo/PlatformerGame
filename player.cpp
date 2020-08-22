#include "player.h"

#include "file_manager.h"
#include "events.h"
#include <stdio.h>

//called when entity is created
void player :: init(double _x_pos, double _y_pos)
{
    entity_init();
    x_pos = _x_pos;
    y_pos = _y_pos;
}

//called every physics frame
void player :: update(double dt, const map &Map, const events &Events)
{
    //walk
    if(Events.left_held)
    {
        x_vel = -120;
        texture = 2;
    }
    else if(Events.right_held)
    {
        x_vel = 120;
        texture = 3;
    }
    else
    {
        x_vel = 0;
        texture = 1;
    }
    //jump
    if(wall_collisions&0b0010)
    {
        airjumps_left = airjumps;
    }
    if(Events.jump_pressed && (wall_collisions&0b0010))
    {
        y_vel = -200;  
    }
    else if(Events.jump_pressed && airjumps_left>0)
    {
        airjumps_left -= 1;
        y_vel = -200;
    }
    //gravity
    y_acc = 400;
    
    //move entity
    entity_move(dt);
    wall_collisions = entity_wall_collisions(Map, true);
}

//called when entity is destroyed
void player :: kill()
{
}