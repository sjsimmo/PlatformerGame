#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>

class settings;

class events {
private:
    SDL_Event event;
    
public:
    void manage(settings &Settings);
    //Control events
    bool quit_pressed = false;
    
    //Keyboard events
    bool s_pressed = false;
    bool left_pressed = false;
    bool right_pressed = false;
    bool up_pressed = false;
    bool down_pressed = false;
    int active_layer = 1;
    //Mouse events
    bool mouse_left_held = false;
    bool mouse_right_held = false;
    int mouse_x = 0;
    int mouse_y = 0;
    unsigned char scroll = 0;
};

#endif