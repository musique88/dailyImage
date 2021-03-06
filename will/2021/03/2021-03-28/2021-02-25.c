#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../../../libs/stb_image_write.h"
#include "../../../libs/buffers/bufferutils.h"
#include "../../../libs/shapes.h"
#include <math.h>

#define WIDTH 256
#define HEIGHT 256

void main()
{
    time_t t = time(0);
    struct Buffer* buffer = create_empty_buffer((struct Vector2i){WIDTH, HEIGHT});
    srand(time(NULL));

    int arrsize = HEIGHT;

    struct ColoredLine line[arrsize]; 
    for(int i = 0; i < arrsize; i++)
    {
        line[i] = (struct ColoredLine){(struct Line){
            (struct Vector2f){ 0, i},
            (struct Vector2f){ HEIGHT-1, i},
        },generate_random_color(false)};

    }

    write_buffer_from_colored_lines(buffer, line, arrsize);
    struct Buffer* buffer2 = create_empty_buffer((struct Vector2i){WIDTH, HEIGHT});
    set_background(buffer2, generate_random_color(false));

    for(int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {   
            float value = i + (sin((float)j/30.f) * WIDTH);
            if (value < WIDTH*HEIGHT && value >= 0) 
                buffer2->colors[i + j * WIDTH] = buffer->colors[(int)value];
        }
    }
    unsigned char* data = pixel_values_to_uchar(buffer2);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}