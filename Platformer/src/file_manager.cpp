//Loads data from text files
#include "file_manager.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <SDL.h>

//TODO - maybe rewrite using SDL2
int file_manager::load_var(const char* var, FILE *file)
{
    char buff[255];
    char *arg;
    rewind(file);
    rewind(file);
    while(!feof(file))
    {
        fgets(buff, 255, file);
        if(strncmp(buff, var, strlen(var)) == 0)
        {
            arg = strchr(buff,'=');
            arg++;
            strtok(arg, "\n");
            return atoi(arg);
        }
    }
    printf("file manager error: variable '%s' does not exist!\n", var);
    return -1;
}

SDL_Keycode file_manager::load_key(const char* var, FILE *file)
{
    char buff[255];
    char *arg;
    rewind(file);
    rewind(file);
    while(!feof(file))
    {
        fgets(buff, 255, file);
        if(strncmp(buff, var, strlen(var)) == 0)
        {
            arg = strchr(buff,'=');
            arg++;
            strtok(arg, "\n");
            return SDL_GetKeyFromName(arg);
        }
    }
    printf("file manager error: variable '%s' does not exist!\n", var);
    return SDLK_UNKNOWN;
}

//TODO - maybe rewrite using SDL2
void file_manager::load_settings(settings &Settings)
{
    //open file in read only mode
    FILE *settingsCFG;
    settingsCFG = fopen(Settings.file_name,"r");
    //load file data into Settings
    Settings.window_width = load_var("window_width", settingsCFG);
    Settings.window_height = load_var("window_height", settingsCFG);
    Settings.vsync = load_var("vsync", settingsCFG);
    Settings.antialiasing = load_var("antialiasing", settingsCFG);
    Settings.fullscreen = load_var("fullscreen", settingsCFG);
    Settings.key_moveleft = load_key("key_moveleft", settingsCFG);
    Settings.key_moveright = load_key("key_moveright", settingsCFG);
    Settings.key_jump = load_key("key_jump", settingsCFG);
    Settings.key_duck = load_key("key_duck", settingsCFG);
    Settings.key_shoot = load_key("key_shoot", settingsCFG);
    //close file
    fclose(settingsCFG);
}

void file_manager::load_map(map &Map)
{
    //open file
    SDL_RWops* file = SDL_RWFromFile(Map.file_name, "rb");
    //read data
    for(int l=0; l<Map.layers; l++)
    {
        for(int y=0; y<Map.height; y++)
        {
            for(int x=0; x<Map.width; x++)
            {
                Map.data[l][y][x] = SDL_ReadU8(file);
            }
        }
    }
    //close file
    SDL_RWclose(file);
}

void file_manager::save_map(const map &Map)
{
    //open file
    SDL_RWops* file = SDL_RWFromFile(Map.file_name, "wb");
    //write data
    for(int l=0; l<Map.layers; l++)
    {
        for(int y=0; y<Map.height; y++)
        {
            for(int x=0; x<Map.width; x++)
            {
                SDL_WriteU8(file, Map.data[l][y][x]);
            }
        }
    }
    //close file
    SDL_RWclose(file);
}