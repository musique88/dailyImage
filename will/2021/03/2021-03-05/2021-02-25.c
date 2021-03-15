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
    int max_value = 10000;

    struct ColoredLine line = {
        (struct Line) {
            {0, 0},
            {rand()%max_value, rand()%max_value}}, 
        generate_random_color(false)};
    struct Buffer* rendered_line = render_colored_line(line);
    struct PositionedBuffer positioned_rendered_line = {rendered_line, (struct Vector2i) {0,0}};
    stack_buffer_w_loop(buffer, &positioned_rendered_line);
    struct ColoredLine line2 = {
        (struct Line) {
            {0, 0},
            {rand()%max_value, rand()%max_value}}, 
        generate_random_color(false)};
    struct Buffer* rendered_line2 = render_colored_line(line2);
    struct PositionedBuffer positioned_rendered_line2 = {rendered_line2, (struct Vector2i) {0,0}};
    stack_buffer_w_loop(buffer, &positioned_rendered_line2);
    struct ColoredLine line3 = {
        (struct Line) {
            {0, 0},
            {rand()%max_value, rand()%max_value}}, 
        generate_random_color(false)};
    struct Buffer* rendered_line3 = render_colored_line(line3);
    struct PositionedBuffer positioned_rendered_line3 = {rendered_line3, (struct Vector2i) {0,0}};
    stack_buffer_w_loop(buffer, &positioned_rendered_line3);
    free(rendered_line);

    unsigned char* data = pixel_values_to_uchar(buffer);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}