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


float f_x(float x)
{
    return sinf(x/14.f) * 40.f+(x*x)/90.f + 40.f;
}

void main()
{
    time_t t = time(0);
    struct Color colors[WIDTH * HEIGHT];
    struct Buffer buffer = {colors, (struct Vector2i){WIDTH, HEIGHT}};
    srand(time(NULL));

    struct Vector2f positions[WIDTH];
    for(int i = 0; i < WIDTH; i++)
    {
        positions[i] = (struct Vector2f){i, (HEIGHT)-f_x((WIDTH/2)-i)};
    }
    
    int linenum =  WIDTH;
    struct ColoredLine lines[linenum];
    for(int i = 0; i < WIDTH - 1; i++)
    {
        lines[i] = (struct ColoredLine){{(struct Vector2f){i,0},positions[i]}, (struct Color){255-positions[i].y,255,255,255}};
    }

    set_background(&buffer, (struct Color){0,0,0,255});
    //write_buffer_from_pixels(&buffer, positions, WIDTH, (struct Color){255,255,255,255});
    write_buffer_from_colored_lines(&buffer, lines, linenum);

    unsigned char* data = pixel_values_to_uchar(&buffer);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}