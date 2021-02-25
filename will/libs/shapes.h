#pragma once

#include "vector.h"

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