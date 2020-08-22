#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <iosfwd>
#include <SDL.h>

//Contains all saveable configuration settings
struct settings
{
    const char* file_name = "settings.cfg";
    //video settings
    int window_width = 640;
    int window_height = 480;
    bool vsync = false;
    int antialiasing = 0;
    bool fullscreen = false;
    SDL_Keycode key_moveleft = SDLK_LEFT;
    SDL_Keycode key_moveright = SDLK_RIGHT;
    SDL_Keycode key_jump = SDLK_UP;
    SDL_Keycode key_duck = SDLK_DOWN;
    SDL_Keycode key_shoot = SDLK_z;
};

//TODO - Make maps dynamic
struct map
{
    const char* file_name = "assets/world.map";
    static const int width = 800;
    static const int height = 338;
    static const int layers = 3;
    static const int grid_size = 16;
    char data[layers][height][width] = {{{0}}};
};

//loads text files
class file_manager
{
private:
    int load_var(const char* var, FILE* file);
    SDL_Keycode load_key(const char* var, FILE* file);
public:
    //Loads variables into Settings from Settings.file_name
    void load_settings(settings &Settings);

    //Loads data into Map from Map.file_name
    void load_map(map &Map);

    //Saves data frome Map into Map.file_name
    void save_map(const map &Map);
};

#endif