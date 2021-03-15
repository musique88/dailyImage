#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../libs/stb_image_write.h"
#include "../libs/vector.h"
#include "../libs/utils.h"
#include <math.h>
#include "../libs/shapes.h"
#define max_random 255

#define WIDTH  256
#define HEIGHT 256

struct ColoredLine{struct Line l; struct Color c; };

int get_random_number(int maxval){
    return rand() % maxval;
}

float get_slope(struct Line line)
{
    return (line.position_b.y - line.position_a.y)/(line.position_b.x - line.position_a.x);
}

unsigned char line_y(struct Line line, unsigned char x, float slope)
{
    return line.position_a.y + slope * (x - line.position_a.x);
}

void main()
{
    struct Color colors[WIDTH * HEIGHT];

    time_t t = time(0);
    srand(&t);

    // Generate balls positions
    int linenum = 160;
    struct ColoredLine positions[linenum];
    for (int i = 0; i < linenum; i++)
    {
        positions[i] = (struct ColoredLine) {
            (struct Line){
                {get_random_number(WIDTH), get_random_number(HEIGHT)}, 
                {get_random_number(WIDTH), get_random_number(HEIGHT)}}, 
                generate_random_color(false)};
    }

    for (int j = 0; j < HEIGHT; ++j)
    {
        for (int i = 0; i < WIDTH; ++i)
        {
            struct Color *selectedColor = &colors[i + j * WIDTH];
            selectedColor->r = 0;
            selectedColor->g = 0;
            selectedColor->b = 0;
            selectedColor->a = 255;
        }
    }
    
    for (int k = 0; k < linenum; k++)
    {
        struct ColoredLine *line = &positions[k];

        if(line->l.position_b.x < line->l.position_a.x)
        {
            struct Vector2f value = line->l.position_b;
            line->l.position_b = line->l.position_a;
            line->l.position_a = value; 
        }

        float slope = get_slope(line->l);
        for (int i = line->l.position_a.x; i < line->l.position_b.x; ++i)
        {
            colors[i + line_y(line->l, i, slope) * WIDTH] = add_color(colors[i + line_y(line->l, i, slope) * WIDTH], line->c);
        }
    }

    time_t t2 = time(0);

    printf("%d\n", t2-t);

    unsigned char* data = pixel_values_to_uchar(colors, (struct Vector2i){WIDTH, HEIGHT});
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
}