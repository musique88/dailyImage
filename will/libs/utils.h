#pragma once
#include "shapes.h"
#include <stdlib.h>

struct Buffer { struct Color *buffer; struct Vector2i size;};

unsigned char* pixel_values_to_uchar(struct Buffer *b)
{
    unsigned char *data = malloc(sizeof *data * b->size.x * b->size.y * 4);
    int index = 0;
    for (int j = 0; j < b->size.y; ++j)
    {
        for (int i = 0; i < b->size.x; ++i)
        {
            struct Color selectedColor = b->buffer[i + j * b->size.x];
            data[index++] = selectedColor.r; // red value
            data[index++] = selectedColor.g; // green value
            data[index++] = selectedColor.b; // blue value
            data[index++] = selectedColor.a; // alpha value
        }
    }
    return data;
}

float get_slope(struct Line line)
{
    return (line.position_b.y - line.position_a.y)/(line.position_b.x - line.position_a.x);
}

int line_y(struct Line line, int x, float slope)
{
    return line.position_a.y + slope * (x - line.position_a.x);
}

struct ColoredLine{struct Line l; struct Color c; };

void write_buffer_from_colored_lines(struct Buffer *buffer, struct ColoredLine* coloredLines, int linenum)
{
    for (int k = 0; k < linenum; k++)
    {
        struct ColoredLine *line = &coloredLines[k];

        if(line->l.position_b.x < line->l.position_a.x)
        {
            struct Vector2f value = line->l.position_a;
            line->l.position_a = line->l.position_b;
            line->l.position_b = value; 
        }
        float slope = get_slope(line->l);
        int last_y = line->l.position_a.y;
        for (int i = line->l.position_a.x; i < line->l.position_b.x; ++i)
        {
            int current_y = line_y(line->l, i, slope);
            buffer->buffer[i + current_y * buffer->size.x] = blend_color(buffer->buffer[i + current_y * buffer->size.x], line->c, NORMAL);
            int slope_sign = slope < 0 ? -1 : 1;
            for (int j = 1; j < abs(current_y - last_y); j++)
                buffer->buffer[i - 1 + (current_y - (j * slope_sign)) * buffer->size.x] = 
                    blend_color(buffer->buffer[i - 1 + (current_y - (j * slope_sign)) * buffer->size.x], line->c, ADD);
            last_y = current_y;
        }
    }
}

void set_background(struct Color *buffer, struct Vector2i bufferSize, struct Color color)
{
    for (int j = 0; j < bufferSize.y; ++j)
    {
        for (int i = 0; i < bufferSize.x; ++i)
        {
            struct Color *selectedColor = &buffer[i + j * bufferSize.x];
            selectedColor->r = color.r;
            selectedColor->g = color.g;
            selectedColor->b = color.b;
            selectedColor->a = color.a;
        }
    }
}

int get_random_number(int maxval){
    return rand() % maxval;
}

