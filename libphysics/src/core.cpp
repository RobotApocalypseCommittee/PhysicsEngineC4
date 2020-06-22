#include "physics/core.h"

namespace physics {

    Vec2::Vec2(float x, float y) : x(x), y(y) {}

    Vec2 Vec2::operator+(Vec2 b) const {
        return {x + b.x, y + b.y};
    }

    Vec2 Vec2::operator*(float s) const {
        return {x * s, y * s};
    }

    float Vec2::operator*(Vec2 b) const {
        // Dot product of two column matrices
        return x * b.x + y * b.y;
    }
}