#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"
#include "../libs/utils.h"
#include <math.h>

#define WIDTH 256
#define HEIGHT 256

void main()
{
    time_t t = time(0);
    struct Color colors[HEIGHT*WIDTH];
    struct Buffer buffer = {colors, (struct Vector2i){WIDTH, HEIGHT}};
    srand(time(NULL));

    // Generate balls positions
    int linenum = 150;
    struct ColoredLine positions[linenum];
    for (int i = 0; i < linenum; i++)
    {
        positions[i] = (struct ColoredLine) {
            (struct Line){
                {get_random_number(WIDTH), get_random_number(HEIGHT)}, 
                {get_random_number(WIDTH), get_random_number(HEIGHT)}}, 
                generate_random_color(false)};
    }

    set_background(colors, (struct Vector2i){WIDTH,HEIGHT}, (struct Color){0,0,0,255});
    write_buffer_from_colored_lines(&buffer, positions, linenum);

    unsigned char* data = pixel_values_to_uchar(&buffer);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}