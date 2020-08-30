/*
MAP EDITOR CONTROLS:
save:                   s
move camera:            arrow keys
change active layer:    0, 1, 2
select texture          scroll
draw on active layer:   left mouse button
erase on active layer:  right mouse button
*/

//Dependencies
#include "file_manager.h"
#include "map.h"
#include "events.h"
#include "graphics.h"
#include "entity.h"

#include <stdio.h>

//Main program
int main(int argc, char* args[])
{
    //Create objects
    file_manager File_manager; //loads files
    settings Settings; //stores loaded data
    map Map; //stores loaded world data
    events Events; //handles events
    graphics Graphics; //manages windows, graphics resources, and renders everything

    entity Pointer;
    
    //DEBUG - Reset Map to Default;
    //File_manager.save_map(Map);

    //Initialise objects and load game
    File_manager.load_settings(Settings);
    Map.load("assets/world.map");
    Graphics.init(Settings);
    Graphics.load_textures(Map);
    Graphics.update_background();
    Graphics.update_layer(1, Map);
    Graphics.update_layer(2, Map);
    Graphics.update_layer(0, Map); //DEBUG - update physics layer

    Pointer.init();
    Pointer.width = 16;
    Pointer.height = 16;
    //Main game loop
    while(!Events.quit_pressed)
    {
        //Events
        Events.manage(Settings);
        
        //Save Map
        if(Events.s_pressed)
        {
            printf("SAVING MAP...\n");
            Map.save("assets/world.map");
            printf("MAP SAVED!\n");
        }

        //Update Pointer
        Pointer.x_pos = (Events.mouse_x/2+Graphics.camera_x_pos)/Map.grid_size*Map.grid_size;
        Pointer.y_pos = (Events.mouse_y/2+Graphics.camera_y_pos)/Map.grid_size*Map.grid_size;
        Pointer.texture = Events.scroll;

        //Draw & Erase
        if(Events.mouse_left_held)
        {
            Map.set_data((Events.mouse_x/2+Graphics.camera_x_pos)/Map.grid_size, (Events.mouse_y/2+Graphics.camera_y_pos)/Map.grid_size, Events.active_layer, Events.scroll);
        }
        else if(Events.mouse_right_held)
        {
            Map.set_data((Events.mouse_x/2+Graphics.camera_x_pos)/Map.grid_size, (Events.mouse_y/2+Graphics.camera_y_pos)/Map.grid_size, Events.active_layer, 0x00);
            Pointer.texture = 0x00;
        }

        //Move Camera
        if(Events.left_pressed && Graphics.camera_x_pos > 0)
        {
            Graphics.camera_x_pos -= Graphics.camera_width;
            printf("CAMERA POS x: %d    y: %d\n", Graphics.camera_x_pos/Graphics.camera_width, Graphics.camera_y_pos/Graphics.camera_height);
        }
        else if(Events.right_pressed && Graphics.camera_x_pos < Map.width*Map.grid_size - Graphics.camera_width)
        {
            Graphics.camera_x_pos += Graphics.camera_width;
            printf("CAMERA POS x: %d    y: %d\n", Graphics.camera_x_pos/Graphics.camera_width, Graphics.camera_y_pos/Graphics.camera_height);
        }
        
        if(Events.up_pressed && Graphics.camera_y_pos > 0)
        {
            Graphics.camera_y_pos -= Graphics.camera_height;
            printf("CAMERA POS x: %d    y: %d\n", Graphics.camera_x_pos/Graphics.camera_width, Graphics.camera_y_pos/Graphics.camera_height);
        }
        else if(Events.down_pressed && Graphics.camera_y_pos < Map.height*Map.grid_size - Graphics.camera_height*2)
        {
            Graphics.camera_y_pos += Graphics.camera_height;
            printf("CAMERA POS x: %d    y: %d\n", Graphics.camera_x_pos/Graphics.camera_width, Graphics.camera_y_pos/Graphics.camera_height);
        }

        //Graphics
        Graphics.update_layer(1, Map);
        Graphics.update_layer(2, Map);
        Graphics.update_layer(0, Map);

        Graphics.draw_background();
        Graphics.draw_layer(1);
        Graphics.draw_layer(2);
        Graphics.draw_layer(0); //DEBUG - draw physics layer
        Graphics.draw_texture_pack_entity(Pointer);
        Graphics.update_window();
    }

    //Cleanup and exit
    Graphics.cleanup();
    return 0;
}