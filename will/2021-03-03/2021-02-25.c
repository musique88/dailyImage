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
    int max_value = 100;

    struct ColoredCircle circles[max_value];

    for (int i = 0; i < max_value; i++)
    {
        circles[i] = (struct ColoredCircle){(struct Circle){(struct Vector2f){rand()%WIDTH, rand()%HEIGHT}, rand()%40}, generate_random_color(false)};
    }

    set_background(&buffer, (struct Color){0,0,0,255});

    write_buffer_from_colored_circles(&buffer, circles, max_value);

    unsigned char* data = pixel_values_to_uchar(&buffer);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}