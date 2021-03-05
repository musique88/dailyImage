#pragma once
#include "vector.h"
#include "buffers/bufferutils.h"
#include "shapes/circle.h"
#include "shapes/line.h"
#include "shapes/triangle.h"

struct Rectangle{
    struct Vector2f position;
    struct Vector2f size;
};

void write_buffer_from_pixels(struct Buffer *buffer, struct Vector2f* pixels, int pixelcount, struct Color color)
{
    for (int k = 0; k < pixelcount; k++)
    {
        if (
            (int)pixels[k].x + (int)pixels[k].y * buffer->size.x < buffer->size.x * buffer->size.y &&
            (int)pixels[k].x + (int)pixels[k].y * buffer->size.x > 0)
            buffer->colors[(int)pixels[k].x + (int)pixels[k].y * buffer->size.x] = color;
        else
            printf("Position[%d,%d], index: %d cannot be drawn\n", (int)pixels[k].x, (int)pixels[k].y,k);
    }
}

