#pragma once
#include "../vector.h"
#include "../buffers/bufferutils.h"

struct Line{
    struct Vector2f position_a;
    struct Vector2f position_b;
};

struct ColoredLine{struct Line l; struct Color c; };


float get_slope(struct Line line)
{
    if (line.position_b.x - line.position_a.x)
        return 0;
    return (line.position_b.y - line.position_a.y)/(line.position_b.x - line.position_a.x);
}

int line_y(struct Line line, int x, float slope)
{
    return line.position_a.y + slope * (x - line.position_a.x);
}

int line_x(struct Line line, int y, float slope)
{
    return line.position_a.x + (1.f/slope) * (y - line.position_a.y);
}

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
        float slope = get_slope(line->l);
        if (fabs(slope) < 1)
        {
            if(line->l.position_b.x < line->l.position_a.x)
            {
                struct Vector2f value = line->l.position_a;
                line->l.position_a = line->l.position_b;
                line->l.position_b = value; 
            }
            for (int i = line->l.position_a.x; i < line->l.position_b.x; ++i)
            {
                int current_y = line_y(line->l, i, slope);
                if (i + current_y * buffer->size.x < buffer->size.x * buffer->size.y &&
                    i + current_y * buffer->size.x > 0)
                    buffer->colors[i + current_y * buffer->size.x] = blend_color(buffer->colors[i + current_y * buffer->size.x], line->c, NORMAL);
                // else
                //     printf("Position[%d,%d], from line: %d cannot be drawn\n", i, current_y,k);
            }
        }
        else
        {
            if(line->l.position_b.y < line->l.position_a.y)
            {
                struct Vector2f value = line->l.position_a;
                line->l.position_a = line->l.position_b;
                line->l.position_b = value; 
            }
            for (int i = line->l.position_a.y; i < line->l.position_b.y; ++i)
            {
                int current_x = line_x(line->l, i, slope);
                if (current_x + i * buffer->size.x < buffer->size.x * buffer->size.y &&
                    current_x + i * buffer->size.x > 0)
                    buffer->colors[current_x + i * buffer->size.x] = blend_color(buffer->colors[current_x + i * buffer->size.x], line->c, NORMAL);
                // else
                //     printf("Position[%d,%d], from line: %d cannot be drawn\n", current_x, i,k);
            }
        }
    }
}

void write_buffer_from_lines(struct Buffer *buffer, struct Line* lines, int linenum, struct Color color)
{
    for (int k = 0; k < linenum; k++)
    {
        struct Line *line = &lines[k];
        float slope = get_slope(*line);
        if (fabs(slope) < 1)
        {
            if(line->position_b.x < line->position_a.x)
            {
                struct Vector2f value = line->position_a;
                line->position_a = line->position_b;
                line->position_b = value; 
            }
            for (int i = line->position_a.x; i < line->position_b.x; ++i)
            {
                int current_y = line_y(*line, i, slope);
                buffer->colors[i + current_y * buffer->size.x] = blend_color(buffer->colors[i + current_y * buffer->size.x], color, NORMAL);
            }
        }
        else
        {
            if(line->position_b.y < line->position_a.y)
            {
                struct Vector2f value = line->position_a;
                line->position_a = line->position_b;
                line->position_b = value; 
            }
            for (int i = line->position_a.y; i < line->position_b.y; ++i)
            {
                int current_x = line_x(*line, i, slope);
                buffer->colors[current_x + i * buffer->size.x] = blend_color(buffer->colors[current_x + i * buffer->size.x], color, NORMAL);
            }
        }
    }
}