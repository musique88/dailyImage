#pragma once
#include "../utils.h"
#include <stdlib.h>
#include <stdio.h>

void set_background(struct Buffer *buffer, struct Color color)
{
    for (int j = 0; j < buffer->size.y; ++j)
    {
        for (int i = 0; i < buffer->size.x; ++i)
        {
            struct Color *selectedColor = &buffer->colors[i + j * buffer->size.x];
            selectedColor->r = color.r;
            selectedColor->g = color.g;
            selectedColor->b = color.b;
            selectedColor->a = color.a;
        }
    }
}

struct Buffer copy_buffer(struct Buffer *buffer)
{
    struct Color new_colors[buffer->size.x * buffer->size.y];
    struct Buffer new_buffer = {new_colors, (struct Vector2i){buffer->size.x, buffer->size.y}};
    for (int j = 0; j < buffer->size.y; ++j)
        for (int i = 0; i < buffer->size.x; ++i)
            new_buffer.colors[i + j * buffer->size.x] = buffer->colors[i + j * buffer->size.x];
    return new_buffer;
}

unsigned char* pixel_values_to_uchar(struct Buffer *b)
{
    unsigned char *data = malloc(sizeof *data * b->size.x * b->size.y * 4);
    int index = 0;
    for (int j = 0; j < b->size.y; ++j)
    {
        for (int i = 0; i < b->size.x; ++i)
        {
            struct Color selectedColor = b->colors[i + j * b->size.x];
            data[index++] = selectedColor.r; // red value
            data[index++] = selectedColor.g; // green value
            data[index++] = selectedColor.b; // blue value
            data[index++] = selectedColor.a; // alpha value
        }
    }
    return data;
}