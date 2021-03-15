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

struct ColoredCircle{struct Circle ci; struct Color co; };

int get_random_number(int maxval){
    return rand() % maxval;
}

void main()
{
    struct Color colors[WIDTH * HEIGHT];

    time_t t = time(0);
    srand(&t);

    // Generate balls positions
    int ballnum = 240;
    struct ColoredCircle positions[ballnum];
    for (int i = 0; i < ballnum; i++)
    {
        positions[i] = (struct ColoredCircle) {(struct Circle){{get_random_number(WIDTH), get_random_number(HEIGHT)}, get_random_number(30)}, generate_random_color(false)};
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
            for (int k = 0; k < ballnum; k++)
            {
                struct ColoredCircle circle = positions[k];
                struct Vector2f position = {(float)i, (float)j};
                float distance = v2f_get_length(position, circle.ci.position);

                float color_amp = 0;
                if (distance < circle.ci.radius)
                {
                    color_amp = ((circle.ci.radius-distance)/circle.ci.radius);

                    float rvalue = (float)selectedColor->r + (float)circle.co.r*color_amp;
                    float gvalue = (float)selectedColor->g + (float)circle.co.g*color_amp;
                    float bvalue = (float)selectedColor->b + (float)circle.co.b*color_amp;

                    selectedColor->r = rvalue > 255 ? 255 : rvalue;
                    selectedColor->g = gvalue > 255 ? 255 : gvalue;
                    selectedColor->b = bvalue > 255 ? 255 : bvalue;
                }
            }
        }
    }

    time_t t2 = time(0);

    printf("%d\n", t2-t);

    unsigned char* data = pixel_values_to_uchar(colors, (struct Vector2i){WIDTH, HEIGHT});
    stbi_write_png("2021-02-21.png", WIDTH, HEIGHT, 4, data, WIDTH * 4);
    free(data);
}