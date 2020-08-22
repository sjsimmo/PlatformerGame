#include "bob.h"

#include "file_manager.h"

//called when entity is created
void bob :: init(double _x_pos, double _y_pos)
{
    entity_init();
    x_pos = _x_pos;
    y_pos = _y_pos;
    texture = 1;
}

//called every physics frame
void bob :: update(double dt, const map &Map, const events &Events)
{
    entity_move(dt);
    entity_wall_collisions(Map, true);
}

//called when entity is destroyed
void bob :: kill()
{
}