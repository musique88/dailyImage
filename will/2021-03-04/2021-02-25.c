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
    int max_value = 100;

    struct Circle circle = {(struct Vector2f){0,0}, rand()%(WIDTH/2)};
    struct Buffer* rendered_circle = render_circle(circle, generate_random_color(false));
    struct PositionedBuffer positioned_rendered_circle = {rendered_circle, (struct Vector2i) {rand()%WIDTH,rand()%HEIGHT}};
    set_background(buffer, (struct Color){0,0,0,0});
    stack_buffer_w_loop(buffer, &positioned_rendered_circle);
    free(rendered_circle);

    unsigned char* data = pixel_values_to_uchar(buffer);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}