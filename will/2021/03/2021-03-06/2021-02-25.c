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
    int arr_length = 50;
    struct Buffer* rendered_lines[arr_length];
    struct PositionedBuffer positioned_rendered_lines[arr_length];

    for(int i = 0; i< arr_length; i++)
    {
        rendered_lines[i] = render_colored_line(
            (struct ColoredLine){(struct Line) {{rand()%max_value, rand()%max_value},{rand()%max_value, rand()%max_value}}, generate_random_color(false)});
        positioned_rendered_lines[i] = (struct PositionedBuffer){rendered_lines[i], (struct Vector2i) {0,0}};
    }

    stack_buffers_w_loop(buffer, positioned_rendered_lines, arr_length);
    
    //free(rendered_lines);

    unsigned char* data = pixel_values_to_uchar(buffer);
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
    time_t t2 = time(0);
    printf("%ld\n", t2-t);
}