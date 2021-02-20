#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define RAND_MAX 255

#define WIDTH 256
#define HEIGHT 256

void main()
{
    time_t t;

    unsigned char data[WIDTH * HEIGHT * 4];
    int index = 0;
    srand((unsigned) time(&t));

    for (int j = 0; j < HEIGHT; ++j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            
            data[index++] = rand(); // red value
            data[index++] = rand(); // green value
            data[index++] = rand(); // blue value
            data[index++] = 255; // alpha value
        }
    }
    stbi_write_png("21-02-20.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
}