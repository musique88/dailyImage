#pragma once
#include "../vector.h"
#include "../buffers/bufferutils.h"

struct Circle{
    struct Vector2f position;
    float radius;
};

struct ColoredCircle{struct Circle ci; struct Color co;};

struct Buffer* render_circle( struct Circle circle, struct Color color)
{
    struct Vector2i size = {circle.radius * 2, circle.radius * 2};
    struct Buffer* buffer = create_empty_buffer(size);
    for (int i = 0; i < buffer->size.x; i++)
        for (int j = 0; j < buffer->size.y; j++)
            if (v2f_get_length((struct Vector2f){buffer->size.x / 2, buffer->size.y / 2}, (struct Vector2f) {i,j}) < circle.radius)
                buffer->colors[i+j*buffer->size.x] = color;
    return buffer;
}

void write_buffer_from_circle(struct Buffer *buffer, struct Circle circle, struct Color color)
{
    for (int i = 0; i < buffer->size.x; i++)
        for (int j = 0; j < buffer->size.y; j++)
            if (v2f_get_length(circle.position, (struct Vector2f) {i,j}) < circle.radius)
                buffer->colors[i+j*buffer->size.x] = color; 
}

void write_buffer_from_circles(struct Buffer *buffer, struct Circle *circle, int length)
{
    for (int k = 0; k < length; k++)
        for (int i = 0; i < buffer->size.x; i++)
            for (int j = 0; j < buffer->size.y; j++)
                if (v2f_get_length(circle[k].position, (struct Vector2f) {i,j}) < circle[k].radius)
                    buffer->colors[i+j*buffer->size.x] = generate_random_color(false); 
}

void write_buffer_from_colored_circles(struct Buffer *buffer, struct ColoredCircle *circle, int length)
{
    for (int k = 0; k < length; k++)
        for (int i = 0; i < buffer->size.x; i++)
            for (int j = 0; j < buffer->size.y; j++)
                if (v2f_get_length(circle[k].ci.position, (struct Vector2f) {i,j}) < circle[k].ci.radius)
                    buffer->colors[i+j*buffer->size.x] = circle[k].co; 
}