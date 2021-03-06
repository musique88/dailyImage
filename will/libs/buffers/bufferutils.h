#pragma once
#include "../utils.h"
#include <stdlib.h>
#include <stdio.h>

struct Buffer* create_empty_buffer(struct Vector2i size) 
{
    struct Color* colors = malloc(sizeof(struct Color) * size.x * size.y);
    struct Buffer* buffer = malloc(sizeof(struct Buffer));
    buffer->size = size;
    buffer->colors = colors;
    for (int i = 0; i < size.x; i++)
        for (int j = 0; j < size.y; j++)
            buffer->colors[i + j*size.x] = (struct Color){0,0,0,0};
    return buffer;
}

void stack_buffer(struct Buffer *buffer, struct PositionedBuffer *buffer2)
{
    for (int i = 0; i < buffer2->buffer->size.x; i++)
    {
        for (int j = 0; j < buffer2->buffer->size.y; j++)
        {
            struct Vector2i position = {i + buffer2->position.x, j + buffer2->position.y};
            if (position.x < buffer->size.x && position.y < buffer->size.y)
                buffer->colors[position.x + position.y * buffer->size.x] = buffer2->buffer->colors[i + j * buffer2->buffer->size.x];
        }
    }
}

void stack_buffer_w_loop(struct Buffer *buffer, struct PositionedBuffer *buffer2)
{
    for (int i = 0; i < buffer2->buffer->size.x; i++)
    {
        for (int j = 0; j < buffer2->buffer->size.y; j++)
        {
            struct Vector2i position = {i + buffer2->position.x, j + buffer2->position.y};
            if (!color_is_the_same(buffer2->buffer->colors[i + j * buffer2->buffer->size.x], (struct Color){0,0,0,0}))
                buffer->colors[position.x%(buffer->size.x) + position.y%(buffer->size.y) * buffer->size.x] = buffer2->buffer->colors[i + j * buffer2->buffer->size.x];
        }
    }
}

void stack_buffer_w_enlarge(struct Buffer *buffer, struct PositionedBuffer *buffer2)
{
    // TODO
    if (buffer2->position.x + buffer2->buffer->size.x < buffer->size.x &&
        buffer2->position.y + buffer2->buffer->size.y < buffer->size.y)
    for (int i = 0; i < buffer2->buffer->size.x; i++)
    {
        for (int j = 0; j < buffer2->buffer->size.y; j++)
        {
            struct Vector2i position = {i + buffer2->position.x, j + buffer2->position.y};
            if (position.x < buffer->size.x && position.y < buffer->size.y)
                buffer->colors[position.x + position.y * buffer->size.x] = buffer2->buffer->colors[i + j * buffer2->buffer->size.x];
        }
    }
}

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