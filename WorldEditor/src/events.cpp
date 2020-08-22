//Handles events including keyboard and mouse input etc. Uses SDL2.
#include "events.h"
#include "file_manager.h"
#include <stdio.h>
#include <SDL.h>

void events::manage(settings &Settings)
{
    s_pressed = false;
    left_pressed = false;
    right_pressed = false;
    up_pressed = false;
    down_pressed = false;

    while(SDL_PollEvent(&event) != 0)
    {
        switch(event.type)
        {
        case SDL_QUIT:
            quit_pressed = true;
            break;

        case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
            {
            case SDLK_s:
            {
                s_pressed = true;
                break;
            }
            case SDLK_LEFT:
                left_pressed = true;
                break;
            case SDLK_RIGHT:
                right_pressed = true;
                break;
            case SDLK_UP:
                up_pressed = true;
                break;
            case SDLK_DOWN:
                down_pressed = true;
                break;
            case SDLK_0:
                active_layer = 0;
                printf("ACTIVE LAYER: %d\n", active_layer);
                break;
            case SDLK_1:
                active_layer = 1;
                printf("ACTIVE LAYER: %d\n", active_layer);
                break;
            case SDLK_2:
                active_layer = 2;
                printf("ACTIVE LAYER: %d\n", active_layer);
                break;
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT:
                mouse_left_held = true;
                break;
            case SDL_BUTTON_RIGHT:
                mouse_right_held = true;
                break;
            }
            break;
            
        case SDL_MOUSEBUTTONUP:
            switch(event.button.button)
            {
            case SDL_BUTTON_LEFT:
                mouse_left_held = false;
                break;
            case SDL_BUTTON_RIGHT:
                mouse_right_held = false;
                break;
            }
            break;

        case SDL_MOUSEMOTION:
            mouse_x = event.button.x;
            mouse_y = event.button.y;
            break;
        
        case SDL_MOUSEWHEEL:
            scroll -= event.wheel.y;
            printf("TEXTURE: %02X\n", scroll);
        }
    }
}