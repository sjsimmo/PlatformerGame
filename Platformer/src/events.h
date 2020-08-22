#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>

class settings;

class events {
private:
    SDL_Event event;
    
public:
    void update(const settings &Settings);
    void clear();
    //Control events
    bool quit_pressed = false;
    
    //Keyboard events
    bool left_pressed = false;
    bool left_held = false;
    bool left_released = false;
    
    bool right_pressed = false;
    bool right_held = false;
    bool right_released = false;
    
    bool jump_pressed = false;
    bool jump_held = false;
    bool jump_released = false;

    bool duck_pressed = false;
    bool duck_held = false;
    bool duck_released = false;
    
    bool shoot_pressed = false;
    bool shoot_held = false;
    bool shoot_released = false;
};

#endif