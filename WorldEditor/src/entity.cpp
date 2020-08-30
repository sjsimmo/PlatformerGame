//Physics enabled entities
#include "entity.h"
#include "file_manager.h"
#include <stdio.h>

void entity::init()
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

void entity::move(double dt)
{
    x_vel += x_acc*dt;
    y_vel += y_acc*dt;
    x_pos += x_vel*dt;
    y_pos += y_vel*dt;
}