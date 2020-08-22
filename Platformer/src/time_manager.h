#ifndef TIME_MANAGER_H
#define TIME_MANAGER_H

//Time management. limits FPS and gets time data. uses SDL2.
class time_manager
{
private:
    unsigned int time;
    unsigned int start_time;
    unsigned int last_time;
    unsigned int fps_frame_counter;
    unsigned int fps_last_time;
    double frames_per_second;
public:
    void init();
    void update();
    double delta_time();
    double current_time();
    double fps(int frames_per_count);
};

#endif