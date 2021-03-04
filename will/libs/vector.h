#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// vector2

struct Vector2i{
    int x;
    int y;
};

struct Vector2f{
    float x;
    float y;
};

struct Vector2f v2f_add(struct Vector2f v1, struct Vector2f v2)
{
    return (struct Vector2f){v1.x + v2.x, v1.y + v2.y};
}

struct Vector2i v2i_add(struct Vector2i v1, struct Vector2i v2)
{
    return (struct Vector2i){v1.x + v2.x, v1.y + v2.y};
}

struct Vector2i v2f_to_v2i(struct Vector2f v)
{
    return (struct Vector2i){floor(v.x), floor(v.y)};
}

struct Vector2f v2i_to_v2f(struct Vector2i v)
{
    return (struct Vector2f){v.x, v.y};
}

float v2i_get_length(struct Vector2i v1, struct Vector2i v2){
    struct Vector2i v12 = {v1.x - v2.x, v1.y - v2.y};
    return sqrt(v12.x * v12.x + v12.y * v12.y);
}

float v2f_get_length(struct Vector2f v1, struct Vector2f v2){
    struct Vector2f v12 = {v1.x - v2.x, v1.y - v2.y};
    return sqrt(v12.x * v12.x + v12.y * v12.y);
}


void printv(struct Vector2f v)
{
    printf("[%f,%f]\n",v.x, v.y);
}

// vector3

struct Vector3i{
    int x;
    int y;
    int z;
};

struct Vector3f{
    float x;
    float y;
    float z;
};

// vector 4

struct Vector4i{
    int x;
    int y;
    int z;
    int w;
};

struct Vector4f{
    float x;
    float y;
    float z;
    float w;
};

struct Color{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

struct Color generate_random_color(bool alpha)
{
    unsigned char alpha_value = 255;
    if (alpha)
        alpha_value = rand()%255;
    struct Color color;
    color.r = rand()%255;
    color.g = rand()%255;
    color.b = rand()%255;
    color.a = alpha_value;

    return color;
}

enum BLENDING_METHOD {
    NORMAL,
    ADD_UNCAPPED,
    ADD
};

struct Color blend_color(struct Color c1, struct Color c2, enum BLENDING_METHOD blending_method)
{
    struct Color value;
    
    unsigned char rvalue;
    unsigned char gvalue;
    unsigned char bvalue;
    unsigned char avalue;
    switch (blending_method)
    {
        case ADD:
            rvalue = c1.r + c2.r;
            gvalue = c1.g + c2.g;
            bvalue = c1.b + c2.b;
            rvalue = rvalue < c1.r ? 255 : rvalue;
            gvalue = gvalue < c1.g ? 255 : gvalue;
            bvalue = bvalue < c1.b ? 255 : bvalue;
            avalue = c1.a;
            break;
        case ADD_UNCAPPED:
            rvalue = c1.r + c2.r;
            gvalue = c1.g + c2.g;
            bvalue = c1.b + c2.b;
            avalue = c1.a;
            break;
        case NORMAL:
            rvalue = c2.r;
            gvalue = c2.g;
            bvalue = c2.b;
            avalue = c2.a;
            break;
    };
    value.r = rvalue;
    value.g = gvalue;
    value.b = bvalue;
    value.a = avalue;

    return value;
}

struct Vector2f v2f_negate(struct Vector2f v)
{
    return (struct Vector2f){-v.x, -v.y};
}