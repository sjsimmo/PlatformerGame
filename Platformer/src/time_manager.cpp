//Time management system. Uses SDL2.
#include "time_manager.h"

#include <SDL.h>
#include <stdio.h>

void time_manager::init()
{
    time = SDL_GetTicks();
    start_time = time;
    last_time = time;
}

void time_manager::update()
{
    last_time = time;
    time = SDL_GetTicks();
}

double time_manager::current_time()
{
    return (double) (time - start_time)/1000.0;
}

double time_manager::delta_time()
{
    return (double) (time - last_time)/1000.0;
}

double time_manager::fps(int frames_per_count)
{
    fps_frame_counter ++;
    if(fps_frame_counter >= frames_per_count)
    {
        frames_per_second = (double) frames_per_count*1000.0/(time-fps_last_time);
        fps_last_time = time;
        fps_frame_counter = 0;
        printf("FPS: %f\n", frames_per_second);
    }
    return frames_per_second;
}