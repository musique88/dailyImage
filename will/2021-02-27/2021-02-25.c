#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"
#include "../libs/buffers/bufferutils.h"
#include "../libs/shapes.h"
#include <math.h>

#define WIDTH 256
#define HEIGHT 256

void main()
{
    time_t t = time(0);
    struct Color colors[WIDTH * HEIGHT];
    struct Buffer buffer = {colors, (struct Vector2i){WIDTH, HEIGHT}};
    srand(time(NULL));
    
    int grid_base_distance = 8;
    float dispersedness = 0.8;

    // Generate balls positions
    struct Vector2i pointer_dimensions = {WIDTH/grid_base_distance, HEIGHT/grid_base_distance};
    int pos_num = pointer_dimensions.x * pointer_dimensions.y;
    struct Vector2f positions[pos_num];
    for (int i = 0; i < pos_num; i++)
    {
        positions[i] = (struct Vector2f) {
            ((i%pointer_dimensions.x)*grid_base_distance) + rand()%((int)floor(grid_base_distance*dispersedness)), 
            ((i/pointer_dimensions.x)*grid_base_distance) + rand()%((int)floor(grid_base_distance*dispersedness))};
    }
    int linenum =  (pointer_dimensions.x - 1) * (pointer_dimensions.y - 1) * 3;
    struct ColoredLine lines[linenum];
    for (int i = 0; i < pointer_dimensions.x - 1; i++)
    {
        for (int j = 0; j < pointer_dimensions.y - 1; j++)
        {
            lines[(i + j * (pointer_dimensions.x - 1))*3] = (struct ColoredLine){{
                positions[i + j * pointer_dimensions.x], 
                positions[i + 1 + j * pointer_dimensions.x]},
                generate_random_color(false)};
            lines[(i + j * (pointer_dimensions.x - 1))*3 + 1] = (struct ColoredLine){{
                positions[i + j * pointer_dimensions.x], 
                positions[i + (j+1) * pointer_dimensions.x]},
                generate_random_color(false)};
            lines[(i + j * (pointer_dimensions.x - 1))*3 + 2] = (struct ColoredLine){{
                positions[i + j * pointer_dimensions.x], 
                positions[i + 1 + (j+1) * pointer_dimensions.x]},
                generate_random_color(false)};
        }
    }

    set_background(&buffer, (struct Color){0,0,0,255});
    write_buffer_from_colored_lines(&buffer, lines, linenum);

    unsigned char* data = pixel_values_to_uchar(&buffer);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}