#include <cmath>
#include <physics/world.h>


#include "physics/core.h"

namespace physics {

    Vec2::Vec2(float x, float y) : x(x), y(y) {}

    Vec2 Vec2::operator+(Vec2 b) const {
        return {x + b.x, y + b.y};
    }

    float Vec2::magnitude() const {
        return std::sqrtf(x*x + y*y);
    }

    float Vec2::sqrMagnitude() const {
        return x*x + y*y;
    }

    Vec2 Vec2::normalized() const {
        return {x/magnitude(), y/magnitude()};
    }

    Vec2 Vec2::operator-(Vec2 b) const {
        return {x - b.x, y - b.y};
    }

    Vec2 Vec2::operator*(float s) const {
        return {x * s, y * s};
    }

    float distance(Vec2 a, Vec2 b) {
        return (a-b).magnitude();
    }

    float Vec2::operator*(Vec2 b) const {
        // Dot product of two column matrices
        return x * b.x + y * b.y;
    }

    Vec2::Vec2() : x(0), y(0) {}

    Vec2 Vec2::operator/(float s) const {
        return {x / s, y / s};
    }

    bool AABB::intersects(const AABB other) const {
        return !(other.max.x < min.x || other.min.x > max.x || other.max.y < min.y || other.min.y > max.y);
    }
}