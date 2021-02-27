#pragma once
#include "vector.h"
#include "buffers/bufferutils.h"

struct Circle{
    struct Vector2f position;
    float radius;
};

struct Rectangle{
    struct Vector2f position;
    struct Vector2f size;
};

struct Line{
    struct Vector2f position_a;
    struct Vector2f position_b;
};

float get_slope(struct Line line)
{
    return (line.position_b.y - line.position_a.y)/(line.position_b.x - line.position_a.x);
}

int line_y(struct Line line, int x, float slope)
{
    return line.position_a.y + slope * (x - line.position_a.x);
}

struct ColoredLine{struct Line l; struct Color c; };

struct Buffer render_colored_line(struct ColoredLine coloredline)
{
    int width = abs(coloredline.l.position_a.x - coloredline.l.position_b.x);
    int height = abs(coloredline.l.position_a.y - coloredline.l.position_b.y);

    struct Color colors[width * height];
    struct Buffer buffer = {colors, (struct Vector2i){width, height}};
    set_background(&buffer, (struct Color){0,0,0,0});
    struct ColoredLine line = coloredline;
    if(line.l.position_b.x < line.l.position_a.x)
    {
        struct Vector2f value = line.l.position_a;
        line.l.position_a = line.l.position_b;
        line.l.position_b = value; 
    }
    float slope = get_slope(line.l);
    int last_y = line.l.position_a.y;
    for (int i = line.l.position_a.x; i < line.l.position_b.x; ++i)
    {
        int current_y = line_y(line.l, i, slope);
        buffer.colors[i + current_y * buffer.size.x] = line.c;
        int slope_sign = slope < 0 ? -1 : 1;
        for (int j = 1; j < abs(current_y - last_y); j++)
            buffer.colors[i - 1 + (current_y - (j * slope_sign)) * buffer.size.x] = line.c;
        last_y = current_y;
    }
    return buffer;
}

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
            buffer->colors[i + current_y * buffer->size.x] = blend_color(buffer->colors[i + current_y * buffer->size.x], line->c, NORMAL);
            int slope_sign = slope < 0 ? -1 : 1;
            for (int j = 1; j < abs(current_y - last_y); j++)
                buffer->colors[i - 1 + (current_y - (j * slope_sign)) * buffer->size.x] = 
                    blend_color(buffer->colors[i - 1 + (current_y - (j * slope_sign)) * buffer->size.x], line->c, NORMAL);
            last_y = current_y;
        }
    }
}
