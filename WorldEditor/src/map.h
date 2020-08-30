#ifndef MAP_H
#define MAP_H

class map
{
private:  
    char* data;
public:
    map();
    ~map();
    void load(const char* file_name);
    void save(const char* file_name);
    char get_data(int x, int y, int l) const;
    void set_data(int x, int y, int l, char value);
    int width = 0;
    int height = 0;
    int layers = 0;
    int grid_size = 0;
};

#endif