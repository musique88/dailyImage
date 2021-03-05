#pragma once
#include "../vector.h"
#include "../buffers/bufferutils.h"
#include "line.h"

struct Triangle{
    struct Vector2f position_a;
    struct Vector2f position_b;
    struct Vector2f position_c;
};

void write_buffer_from_triangle(struct Buffer *buffer, struct Triangle triangle, struct Color color)
{
    int length = v2f_get_length(triangle.position_a, triangle.position_b);
    struct Line line = {triangle.position_a, triangle.position_b};
    float slope = get_slope(line);
    struct Line lines[length];
    if (fabs(slope) < 1)
    {
        if(line.position_b.x < line.position_a.x)
        {
            struct Vector2f value = line.position_a;
            line.position_a = line.position_b;
            line.position_b = value; 
        }
        for (int i = line.position_a.x; i < line.position_b.x; ++i)
        {
            int current_y = line_y(line, i, slope);
            lines[i - (int)line.position_a.x] = (struct Line){(struct Vector2f){i, current_y}, triangle.position_c};
        }
    }
    else
    {
        if(line.position_b.y < line.position_a.y)
        {
            struct Vector2f value = line.position_a;
            line.position_a = line.position_b;
            line.position_b = value; 
        }
        for (int i = line.position_a.y; i < line.position_b.y; ++i)
        {
            int current_x = line_x(line, i, slope);            
            lines[i - (int)line.position_a.y] = (struct Line){(struct Vector2f){current_x, i}, triangle.position_c};
        }
    }
    write_buffer_from_lines(buffer, lines, length, color);
}