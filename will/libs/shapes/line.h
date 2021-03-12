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
        return (line.position_b.y - line.position_a.y)/(line.position_b.x - line.position_a.x);
    return (float)((unsigned int)0 - 1);
}

int line_y(struct Line line, int x, float slope)
{
    return line.position_a.y + slope * (x - line.position_a.x);
}

int line_x(struct Line line, int y, float slope)
{
    return line.position_a.x + (1.f/slope) * (y - line.position_a.y);
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

void write_buffer_from_colored_line(struct Buffer *buffer, struct ColoredLine coloredLine)
{
    struct ColoredLine *line = &coloredLine;
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
        }
    }
}

struct Buffer* render_colored_line(struct ColoredLine coloredline)
{
    struct Buffer * buffer = create_empty_buffer((struct Vector2i){
        abs(coloredline.l.position_a.x - coloredline.l.position_b.x), 
        abs(coloredline.l.position_a.y - coloredline.l.position_b.y)}); 
    write_buffer_from_colored_line(buffer, coloredline);
    return buffer;
}