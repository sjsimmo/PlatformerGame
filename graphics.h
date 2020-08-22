#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL.h>

//Forward Declarations
class settings;
class map;
class entity;

//Handles Game Graphics including world drawing and window management. Relies on SDL2.
class graphics
{
private:
    //Game size parameters
    static const int layers = 3;

    //The positions of all entity textures in entity_texture
    SDL_Rect entity_texture_map[256] =
    {
        {0,0,0,0}, //none
        {0,0,12,24}, //player - forward
        {12,0,12,24}, //player - left
        {24,0,12,24}, //player - right
    };

    //Other SDL Variables
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    SDL_Texture* camera = NULL;
    SDL_Rect camera_dstrect;
    SDL_Texture* texture_pack = NULL;
    SDL_Rect texture_map[256];
    SDL_Texture* entity_texture = NULL;
    SDL_Texture* background_texture = NULL;
    SDL_Texture* layer_texture[layers] = {NULL, NULL, NULL};

public:
    //Camera position
    int camera_width = 640;
    int camera_height = 360;
    int camera_x_pos = 0;
    int camera_y_pos = 0;
    //Initialises SDL and creates window according to Settings
    void init(const settings &Settings);
    //Loads texture pack from texture_pack.bmp and skins from skin_pack.bmp and creates layers
    void load_textures(const map &Map);
    //Loads background from background.bmp
    void update_background();
    //Updates layer according to map and camera position
    void update_layer(int layer, const map &Map);
    //Draws background on the window
    void draw_background();
    //Draws layer on the window
    void draw_layer(int layer);
    //Draws entity on the window
    void draw_entity(const entity &entity);
    //Displays next frame
    void update_window();
    //Frees resources and quits SDL
    void cleanup();
};

#endif