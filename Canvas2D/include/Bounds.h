#ifndef BOUNDS
#define BOUNDS

#include "Vector2.h"

class Bounds
{
public:
    Vector2 position, center, size;

    Bounds(float x, float y, float w, float h);
    Bounds(Vector2 position, Vector2 size);

    bool Contains(Vector2 point);
    bool Intersects(Bounds& other);
    bool RayCast(Vector2 origin, Vector2 direction, float& distance);
    bool RayCast(Vector2 origin, Vector2 direction, float rayWidth, float& distance);
};

#endif // !BOUNDS
