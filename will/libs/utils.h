#pragma once
#include "vector.h"
#include <stdlib.h>

unsigned char* pixel_values_to_uchar(struct Color *c, struct Vector2i size)
{
    unsigned char *data = malloc(sizeof *data * size.x * size.y * 4);
    int index = 0;
    for (int j = 0; j < size.y; ++j)
    {
        for (int i = 0; i < size.x; ++i)
        {
            struct Color selectedColor = c[i + j * size.x];
            data[index++] = selectedColor.r; // red value
            data[index++] = selectedColor.g; // green value
            data[index++] = selectedColor.b; // blue value
            data[index++] = selectedColor.a; // alpha value
        }
    }
    return data;
}