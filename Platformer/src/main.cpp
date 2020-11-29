//Dependencies
#include "file_manager.h" 
#include "map.h"
#include"graphics.h"
#include "time_manager.h"
#include "events.h"
#include "entity.h"
#include "player.h"
#include "bob.h"

#include <vector>
#include <stdio.h> //DEBUG

//Main program
int main(int argc, char* args[])
{
    //Create objects
    file_manager File_manager; //loads files
    settings Settings; //stores settings data
    map Map; //stores world data
    time_manager Time_manager; //keeps track of timing and FPS
    events Events; //handles events
    graphics Graphics; //manages windows, graphics resources, and renders everything

    //Initialise objects and load game
    File_manager.load_settings(Settings);
    Map.load("assets/world.map");
    Graphics.init(Settings);
    Graphics.load_textures(Map);
    Graphics.update_background();
    Time_manager.init();

    double physics_timestep = 1.0/240.0;
    double physics_time = 0;
    int old_camera_x_pos = -1;
    int old_camera_y_pos = -1;

    //Create entity list
    std::vector<entity*> Entity;
    Entity.push_back(new player);
    Entity[0]->init(50,275);
    
    //Main game loop
    while(!Events.quit_pressed)
    {
        //Timing
        Time_manager.update();
        Time_manager.fps(60); //DEBUG - FPS counter

        //Events
        Events.update(Settings);

        //Physics
        for(double time=Time_manager.current_time(); physics_time<time; physics_time+=physics_timestep)
        {
            for(int i=0; i<Entity.size(); i++)
            {
                Entity[i]->update(physics_timestep, Map, Events);
            }
            Events.clear();
        }

        //Camera
        Graphics.camera_x_pos = (int)(Entity[0]->x_pos+6)/Graphics.camera_width*Graphics.camera_width;
        Graphics.camera_y_pos = (int)(Entity[0]->y_pos+12)/Graphics.camera_height*Graphics.camera_height;
        if(old_camera_x_pos != Graphics.camera_x_pos || old_camera_y_pos != Graphics.camera_y_pos)
        {
            Graphics.update_layer(1, Map);
            Graphics.update_layer(2, Map);
            old_camera_x_pos = Graphics.camera_x_pos;
            old_camera_y_pos = Graphics.camera_y_pos;
        }
        
        //Graphics
        Graphics.draw_background();
        Graphics.draw_layer(1);
        for(int i=0; i<Entity.size(); i++)
        {
            Graphics.draw_entity(*Entity[i]);
        }
        Graphics.draw_layer(2);
        Graphics.update_window();
    }

    //Cleanup and exit 
    for(int i=0; i<Entity.size(); i++)
    {
        delete Entity[i];
    }
    Entity.clear();
    Graphics.cleanup();

    return 0;
}