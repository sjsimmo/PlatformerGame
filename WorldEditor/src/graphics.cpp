//Handles SDL graphics functions and renders everything
#include "graphics.h"

#include <SDL.h>
#include <stdio.h>
#include "entity.h"
#include "file_manager.h"

//Creates window
void graphics::init(settings &Settings)
{
    //Initialise SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0) 
    { 
        printf("Failed to initialise SDL. SDL error: %s\n", SDL_GetError()); 
    }
    //Create window and renderer
    window = SDL_CreateWindow("Epic Platformer Game - The Third Attempt (World Editor)", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Settings.window_width, Settings.window_height, SDL_WINDOW_SHOWN);
    if(window == NULL) 
    {
        printf("Failed to create window. SDL error: %s\n", SDL_GetError());
    }
    
    if(Settings.vsync)
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE | SDL_RENDERER_PRESENTVSYNC); 
    }
    else
    {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE);
    }

    if(renderer == NULL) 
    {
        printf("Failed to create renderer. SDL error: %s\n", SDL_GetError());
    }
    //Antialiasing
    if(Settings.antialiasing == 2)
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "2"); //antistropic
    }
    else if(Settings.antialiasing == 1)
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //linear
    } 
    else
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0"); //none
    }
    //Fullscreen
    if(Settings.fullscreen)
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
    }
    //Window padding
    int window_width;
    int window_height;
    SDL_GetWindowSize(window, &window_width, &window_height);
    if((double)window_width/window_height > (double)camera_width/camera_height)
    {
        camera_dstrect = {(window_width - (int)(window_height*((double)camera_width/camera_height)))/2, 0, (int)(window_height*((double)camera_width/camera_height)), window_height};
    }
    else if((double)window_width/window_height < (double)camera_width/camera_height)
    {
        camera_dstrect = {0, (window_height - (int)(window_width*((double)camera_height/camera_width)))/2, window_width, (int)(window_width*((double)camera_height/camera_width))};
    }
    else
    {
        camera_dstrect = {0, 0, window_width, window_height};
    }
    //Draw black screen
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
}

//Creates and loads all nessecary textures
void graphics::load_textures(map &Map)
{
    //Create camera texture
    camera = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, camera_width, camera_height);
    SDL_SetTextureBlendMode(camera, SDL_BLENDMODE_BLEND);    
    //Load texture pack
    SDL_Surface* surface = SDL_LoadBMP("assets/texture_pack.bmp");
    texture_pack = SDL_CreateTextureFromSurface(renderer, surface);
    if(texture_pack == NULL)
    {
        printf("Failed to load assets/texture_pack.bmp. SDL error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);
    //Create rectangles to point to texture pack locations
    for(int j=0; j<16; j++)
    {
        for(int i=0; i<16; i++)
        {
            texture_map[j*16+i] = {i*Map.grid_size, j*Map.grid_size, Map.grid_size, Map.grid_size};
        }
    }
    //Create layer textures
    for(int layer=0; layer<layers; layer++)
    {
        layer_texture[layer] = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, camera_width, camera_height);
        SDL_SetTextureBlendMode(layer_texture[layer], SDL_BLENDMODE_BLEND);        
    }
    //Load entity textures from entity_texture.bmp
    surface = SDL_LoadBMP("assets/entity_texture.bmp");
    entity_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(entity_texture == NULL)
    {
        printf("Failed to load assets/entity_texture.bmp. SDL error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);
}

//Loads background from background.bmp. TODO - add multiple background support
void graphics::update_background()
{
    SDL_Surface* surface = SDL_LoadBMP("assets/background.bmp");
    background_texture = SDL_CreateTextureFromSurface(renderer, surface);
    if(background_texture == NULL)
    {
        printf("Failed to load assets/background.bmp. SDL error: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(surface);
}

//Loads layer using world map and texture pack 
void graphics::update_layer(int layer, map &Map)
{
    //Clear layer
    SDL_SetRenderTarget(renderer, layer_texture[layer]);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);

    //Draw layer according to world map
    for(int y_pos=camera_y_pos-camera_y_pos%Map.grid_size; y_pos < camera_y_pos+camera_height; y_pos+=Map.grid_size)
    {
        for(int x_pos=camera_x_pos-camera_x_pos%Map.grid_size; x_pos < camera_x_pos+camera_width; x_pos+=Map.grid_size)
        {
            char map_data = Map.data[layer][y_pos/Map.grid_size][x_pos/Map.grid_size];
            if(map_data != 0) //skip if empty space
            {
                SDL_Rect draw_location = {x_pos-camera_x_pos, y_pos-camera_y_pos, texture_map[map_data].w, texture_map[map_data].h};
                SDL_RenderCopy(renderer, texture_pack, &texture_map[map_data], &draw_location);
            }
        }
    }
    SDL_SetRenderTarget(renderer, camera);
}

void graphics::draw_background()
{
    SDL_RenderCopy(renderer, background_texture, NULL, NULL);
}

void graphics::draw_layer(int layer)
{
    SDL_RenderCopy(renderer, layer_texture[layer], NULL, NULL);
}

void graphics::draw_entity(const entity &Entity)
{
    SDL_SetRenderTarget(renderer, camera);
    SDL_Rect draw_location = {(int) Entity.x_pos - (int) camera_x_pos, (int) Entity.y_pos - (int) camera_y_pos, (int) entity_texture_map[Entity.texture].w, (int) entity_texture_map[Entity.texture].h};
    SDL_RenderCopy(renderer, entity_texture, &entity_texture_map[Entity.texture], &draw_location);
    
}

void graphics::draw_texture_pack_entity(const entity &Entity)
{
    SDL_SetRenderTarget(renderer, camera);
    SDL_Rect draw_location = {(int) Entity.x_pos - (int) camera_x_pos, (int) Entity.y_pos - (int) camera_y_pos, Entity.width, (int) Entity.height};
    SDL_RenderCopy(renderer, texture_pack, &texture_map[Entity.texture], &draw_location);
}

void graphics::update_window()
{
    //Copy camera to renderer and present renderer to window. Then clear the camera
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, camera, NULL, &camera_dstrect);
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_SetRenderTarget(renderer, camera);
    SDL_RenderClear(renderer);
}

void graphics::cleanup()
{
    //Destroy everything and quit SDL
    SDL_DestroyTexture(texture_pack);
    SDL_DestroyTexture(entity_texture);
    SDL_DestroyTexture(background_texture);
    for(int layer=0; layer<layers; layer++)
    {
        SDL_DestroyTexture(layer_texture[layer]);
    }
    SDL_DestroyTexture(camera);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}