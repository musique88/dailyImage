#pragma once
#include <stdlib.h>
#include "vector.h"

struct Buffer { struct Color *colors; struct Vector2i size;};
struct PositionedBuffer {struct Buffer *buffer; struct Vector2i position;};

int get_random_number(int maxval){
    return rand() % maxval;
}

