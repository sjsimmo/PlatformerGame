//loads, saves, and contains map data. Implemented using SDL2
#include "map.h"

#include <SDL.h>

map::map()
{
    data = new char[width*height*layers];
    for(int i=0; i<width*height*layers; i++)
    {
        data[i]=0;
    }
}

void map::load(const char* file_name)
{
    delete[] data;
    SDL_RWops* file = SDL_RWFromFile(file_name, "rb");
    SDL_RWread(file, &width, sizeof(int), 1);
    SDL_RWread(file, &height, sizeof(int), 1);
    SDL_RWread(file, &layers, sizeof(int), 1);
    SDL_RWread(file, &grid_size, sizeof(int), 1);
    data = new char[width*height*layers];
    SDL_RWread(file, data, sizeof(char), width*height*layers);
    SDL_RWclose(file);
}

void map::save(const char* file_name)
{
    SDL_RWops* file = SDL_RWFromFile(file_name, "wb");
    SDL_RWwrite(file, &width, sizeof(int), 1);
    SDL_RWwrite(file, &height, sizeof(int), 1);
    SDL_RWwrite(file, &layers, sizeof(int), 1);
    SDL_RWwrite(file, &grid_size, sizeof(int), 1);
    SDL_RWwrite(file, data, sizeof(char), width*height*layers);
    SDL_RWclose(file);
}


char map::get_data(int x, int y, int l) const
{
    return data[x+(y+l*height)*width];
}

void map::set_data(int x, int y, int l, char value)
{
    data[x+(y+l*height)*width] = value;
}

map::~map()
{
    delete[] data;
}