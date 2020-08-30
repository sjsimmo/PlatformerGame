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
    if(wall_collisions&0b0010)
    {
        if(Events.left_held)
        {
            x_acc = -walk_acc;
            texture = 2;
            if(x_vel<-walk_vel-x_acc*dt)
            {
                x_vel = -walk_vel;
                x_acc = 0;
            }
        }
        else if(Events.right_held)
        {
            x_acc = walk_acc;
            texture = 3;
            if(x_vel>walk_vel-x_acc*dt)
            {
                x_vel = walk_vel;
                x_acc = 0;
            }
        }
        else
        {
            if(x_vel<-walk_acc*dt)
            {
                x_acc = walk_acc;
            }
            else if(x_vel>walk_acc*dt)
            {
                x_acc = -walk_acc;
            }
            else
            {
                x_vel = 0;
                x_acc = 0;
                texture = 1;
            }    
        }
    }
    //airwalk
    else
    {
        if(Events.left_held)
        {
            x_acc = -air_acc;
            texture = 2;
            if(x_vel<-walk_vel-x_acc*dt)
            {
                x_vel = -walk_vel;
                x_acc = 0;
            }
        }
        else if(Events.right_held)
        {
            x_acc = air_acc;
            texture = 3;
            if(x_vel>walk_vel-x_acc*dt)
            {
                x_vel = walk_vel;
                x_acc = 0;
            }
        }
        else
        {
            if(x_vel<-air_acc*dt)
            {
                x_acc = air_acc;
            }
            else if(x_vel>air_acc*dt)
            {
                x_acc = -air_acc;
            }
            else
            {
                x_vel = 0;
                x_acc = 0;
                texture = 1;
            }    
        }
    }
    
    //jump
    if(wall_collisions&0b0010)
    {
        airjumps_left = airjumps;
        jump_was_pressed = false;
    }
    if(Events.jump_pressed && (wall_collisions&0b0010))
    {
        y_vel = -jump_vel;
        jump_was_pressed = true;
    }
    //walljump
    else if(Events.jump_pressed && (wall_collisions&0b1000))
    {
        y_vel = -walljump_vel;
        x_vel = walljump_x_vel;
        jump_was_pressed = true;
    }
    else if(Events.jump_pressed && (wall_collisions&0b0001))
    {
        y_vel = -walljump_vel;
        x_vel = -walljump_x_vel;
        jump_was_pressed = true;
    }
    //airjump
    else if(Events.jump_pressed && airjumps_left>0)
    { 
        y_vel = -airjump_vel;
        airjumps_left -= 1;
        jump_was_pressed = true;
    }
    //gravity
    if(!Events.jump_held && jump_was_pressed && y_vel<-50)
    {
        y_acc = endjump_acc;
    }
    else
    {
        y_acc = gravity;
    }   
    //wallslide
    if(y_vel>wallslide_vel-y_acc*dt && (wall_collisions&0b1000 || wall_collisions&0b0001))
    {
        y_vel = wallslide_vel-y_acc*dt;
    }

    //move entity
    entity_move(dt);
    wall_collisions = entity_wall_collisions(Map, true);
}

//called when entity is destroyed
void player :: kill()
{
}