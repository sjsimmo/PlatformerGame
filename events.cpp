//Handles events including keyboard and mouse input etc. Uses SDL2.
#include "events.h"
#include "file_manager.h"
#include <stdio.h>
#include <SDL.h>

void events::update(const settings &Settings)
{
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT) 
        {
            quit_pressed = true; 
        }
        else if(event.type == SDL_KEYDOWN)
        {
            if(event.key.keysym.sym == Settings.key_moveleft && !left_held)
            {
                left_pressed = true;
                left_held = true;
            }
            else if(event.key.keysym.sym == Settings.key_moveright && !right_held)
            {
                right_pressed = true;
                right_held = true;
            }
            else if(event.key.keysym.sym == Settings.key_jump && !jump_held)
            {
                jump_pressed = true;
                jump_held = true;
            }
            else if(event.key.keysym.sym == Settings.key_duck && !duck_held)
            {
                duck_pressed = true;
                duck_held = true;
            }
            else if(event.key.keysym.sym == Settings.key_shoot && !shoot_held)
            {
                shoot_pressed = true;
                shoot_held = true;
            }
        }
        else if(event.type == SDL_KEYUP)
        {
            if(event.key.keysym.sym == Settings.key_moveleft)
            {
                left_released = true;
                left_held = false;
            }
            else if(event.key.keysym.sym == Settings.key_moveright)
            {
                right_released = true;
                right_held = false;
            }
            else if(event.key.keysym.sym == Settings.key_jump)
            {
                jump_released = true;
                jump_held = false;
            }
            else if(event.key.keysym.sym == Settings.key_duck)
            {
                duck_released = true;
                duck_held = false;
            }
            else if(event.key.keysym.sym == Settings.key_shoot)
            {
                shoot_released = true;
                shoot_held = false;
            } 
        }
    }
}

void events::clear()
{
    left_pressed = false;
    right_pressed = false;
    jump_pressed = false;
    duck_pressed = false;
    shoot_pressed = false;
    left_released = false;
    right_released = false;
    jump_released = false;
    duck_released = false;
    shoot_released = false;
}