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
    struct Buffer* buffer = create_empty_buffer((struct Vector2i){WIDTH, HEIGHT});
    srand(time(NULL));

    int arrsize = WIDTH + HEIGHT;

    struct ColoredLine line[arrsize]; 
    for(int i = 0; i < arrsize; i++)
    {
        line[i] = (struct ColoredLine){(struct Line){
            (struct Vector2f){  i < WIDTH ? 0: i-WIDTH,
                                i < WIDTH ? HEIGHT-i: 0},
            (struct Vector2f){  i < WIDTH ? i: WIDTH-1,
                                i < WIDTH ? HEIGHT-1: HEIGHT+HEIGHT-i},
        },
        generate_random_color(false)};
    }
    write_buffer_from_colored_lines(buffer, line, arrsize);

    struct Buffer* buffer2 = create_empty_buffer((struct Vector2i){WIDTH, HEIGHT});
    int zoomfactor = 2;
    for (int i = 0; i < buffer2->size.x; i++)
    {
        for (int j = 0; j < buffer2->size.y; j++)
        {
            if (i * zoomfactor < WIDTH && j * zoomfactor < HEIGHT)
                buffer2->colors[i*zoomfactor + j*zoomfactor * buffer->size.x] = buffer->colors[i + j * buffer->size.x];
        }
    }

    unsigned char* data = pixel_values_to_uchar(buffer2);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}