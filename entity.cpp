//Physics enabled entities
#include "entity.h"
#include "file_manager.h"

void entity::entity_init()
{
    x_pos = 0;
    y_pos = 0;
    old_x_pos = x_pos;
    old_y_pos = y_pos;
    x_vel = 0;
    y_vel = 0;
    x_acc = 0;
    y_acc = 0;
    texture = 0;
}

void entity::entity_move(double dt)
{
    
    x_vel += x_acc*dt;
    y_vel += y_acc*dt;
    x_pos += x_vel*dt;
    y_pos += y_vel*dt;
}

char entity::entity_wall_collisions(const map &Map, bool collide)
{
    char direction = 0b0000;
    double try_x_pos;
    double try_y_pos;

    //left collision
    try_x_pos = old_x_pos;
    while(try_x_pos>x_pos && !(direction&0b1000))
    {
        try_x_pos-=Map.grid_size;
        if(try_x_pos<x_pos)
        {
            try_x_pos = x_pos;
        }
        for(try_y_pos = old_y_pos; try_y_pos<y_pos+height-1 && !(direction&0b1000); try_y_pos+=Map.grid_size)
        {
            if(Map.data[0][(int)try_y_pos/Map.grid_size][(int)try_x_pos/Map.grid_size]&0b0001)
            {
                direction |= 0b1000;
                if(collide)
                {
                    x_pos = ((int)try_x_pos/Map.grid_size+1)*Map.grid_size;
                    x_vel = 0;
                }
            }
        }
        if(Map.data[0][(int)(old_y_pos+height-1)/Map.grid_size][(int)try_x_pos/Map.grid_size]&0b0001 && !(direction&0b1000))
        {
            direction |= 0b1000;
            if(collide)
            {
                x_pos = ((int)try_x_pos/Map.grid_size+1)*Map.grid_size;
                x_vel = 0;
            }
        } 
    }
    //right collision
    try_x_pos = old_x_pos+width-1;
    while(try_x_pos<x_pos+width-1 && !(direction&0b0001))
    {
        try_x_pos+=Map.grid_size;
        if(try_x_pos>x_pos+width)
        {
            try_x_pos = x_pos+width;
        }
        for(try_y_pos = old_y_pos; try_y_pos<y_pos+height-1 && !(direction&0b0001); try_y_pos+=Map.grid_size)
        {
            if(Map.data[0][(int)try_y_pos/Map.grid_size][(int)(try_x_pos)/Map.grid_size]&0b1000)
            {
                direction |= 0b0001;
                if(collide)
                {
                    x_pos = ((int)try_x_pos/Map.grid_size)*Map.grid_size - width;
                    x_vel = 0;
                }
            }
        } 
        if(Map.data[0][(int)(old_y_pos+height-1)/Map.grid_size][(int)(try_x_pos)/Map.grid_size]&0b1000 && !(direction&0b0001))
        {
            direction |= 0b0001;
            if(collide)
            {
                x_pos = ((int)try_x_pos/Map.grid_size)*Map.grid_size - width;
                x_vel = 0;
            }
        }
    }
    old_x_pos = x_pos;
    //up collision
    try_y_pos = old_y_pos;
    while(try_y_pos>y_pos && !(direction&0b0100))
    {
        try_y_pos-=Map.grid_size;
        if(try_y_pos<y_pos)
        {
            try_y_pos = y_pos;
        }
        for(try_x_pos = old_x_pos; try_x_pos<x_pos+width-1 && !(direction&0b0100); try_x_pos+=Map.grid_size)
        {
            if(Map.data[0][(int)try_y_pos/Map.grid_size][(int)try_x_pos/Map.grid_size]&0b0010)
            {
                direction |= 0b0100;
                if(collide)
                {
                    y_pos = ((int)try_y_pos/Map.grid_size+1)*Map.grid_size;
                    y_vel = 0;
                }
            }
        }
        if(Map.data[0][(int)try_y_pos/Map.grid_size][(int)(old_x_pos+width-1)/Map.grid_size]&0b0010 && !(direction&0b0100))
        {
            direction |= 0b0100;
            if(collide)
            {
                y_pos = ((int)try_y_pos/Map.grid_size+1)*Map.grid_size;
                y_vel = 0;
            }
        } 
    }
    //down collision
    try_y_pos = old_y_pos+height-1;
    while(try_y_pos<y_pos+height-1 && !(direction&0b0010))
    {
        try_y_pos+=Map.grid_size;
        if(try_y_pos>y_pos+height)
        {
            try_y_pos = y_pos+height;
        }
        for(try_x_pos = old_x_pos; try_x_pos<x_pos+width-1 && !(direction&0b0010); try_x_pos+=Map.grid_size)
        {
            if(Map.data[0][(int)try_y_pos/Map.grid_size][(int)try_x_pos/Map.grid_size]&0b0100)
            {
                direction |= 0b0010;
                if(collide)
                {
                    y_pos = ((int)try_y_pos/Map.grid_size)*Map.grid_size - height;
                    y_vel = 0;
                }
            }
        } 
        if(Map.data[0][(int)(try_y_pos)/Map.grid_size][(int)(old_x_pos+width-1)/Map.grid_size]&0b0100 && !(direction&0b0010))
        {
            direction |= 0b0010;
            if(collide)
            {
                y_pos = ((int)try_y_pos/Map.grid_size)*Map.grid_size - height;
                y_vel = 0;
            }
        }
    }
    old_y_pos = y_pos;
    
    return direction;
}