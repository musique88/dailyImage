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

void write_buffer_from_circle_temp(struct Buffer *buffer, struct Circle circle, struct Color* color)
{
    for (int i = 0; i < buffer->size.x; i++)
    {
        for (int j = 0; j < buffer->size.y; j++)
        {
            struct Vector2f position = (struct Vector2f) {i,j};
            if (v2f_get_length(circle.position, (struct Vector2f) {i,j}) < circle.radius)
            {
                struct Vector2f relativevector = v2f_add(position, v2f_negate(circle.position));
                if (relativevector.x > 0)
                {
                    if (relativevector.y > 0)
                        buffer->colors[i + j * buffer->size.x] = color[0];
                    else
                        buffer->colors[i + j * buffer->size.x] = color[1];
                }
                else
                {
                    if (relativevector.y > 0)
                        buffer->colors[i + j * buffer->size.x] = color[2];
                    else
                        buffer->colors[i + j * buffer->size.x] = color[3];
                }
            }
        }
    }
}

void main()
{
    time_t t = time(0);
    struct Color colors[WIDTH * HEIGHT];
    struct Buffer buffer = {colors, (struct Vector2i){WIDTH, HEIGHT}};
    srand(time(NULL));

    struct Circle circle = (struct Circle) {(struct Vector2f) {WIDTH/2, HEIGHT/2}, 100};

    set_background(&buffer, (struct Color){0,0,0,255});

    struct Color quarters[] = {
        (struct Color) {255,0,0,255},
        (struct Color) {255,255,0,255},
        (struct Color) {0,255,0,255},
        (struct Color) {0,255,255,255},
    };

    write_buffer_from_circle_temp(&buffer, circle, quarters);

    unsigned char* data = pixel_values_to_uchar(&buffer);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}