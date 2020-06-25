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

    Vec2 Vec2::perpendicular() const {
        return {y, -x};
    }

    Vec2& Vec2::operator+=(Vec2 b) {
        x += b.x;
        y += b.y;
        return *this;
    }

    Vec2 &Vec2::operator-=(Vec2 b) {
        x -= b.x;
        y -= b.y;
        return *this;
    }

    bool AABB::intersects(const AABB other) const {
        return !(other.max.x < min.x || other.min.x > max.x || other.max.y < min.y || other.min.y > max.y);
    }

    Mat2x2::Mat2x2(float angle) {
        a = d = std::cosf(angle);
        c = std::sinf(angle);
        b = -c;
    }

    Vec2 Mat2x2::operator*(Vec2 v) const {
        return {a * v.x + b * v.y, c * v.x + d * v.y};
    }

    bool Projection::intersects(Projection other) const {
        return min <= other.max && other.min <= max;
    }

    float Projection::intersection(Projection other) const {
        return std::min(max, other.max) - std::max(min, other.min);
    }

    // TODO maybe make a line struct so you don't need to pass 4 Vec2s, but I dont care atm
    bool intersection(Vec2 start1, Vec2 end1, Vec2 start2, Vec2 end2, Vec2 &out) {
        float v = (end2.x - start2.x) * (start1.y - end1.y) - (start1.x - end1.x) * (end2.y - start2.y);
        if (v == 0) {
            return false;
        }

        float rat1 = ((start2.y - end2.y) * (start1.x - start2.x) + (end2.x - start2.x) * (start1.y - start2.y)) / v;
        float rat2 = ((start1.y - end1.y) * (start1.x - start2.x) + (end1.x - start1.x) * (start1.y - start2.y)) / v;

        if ((rat1 >= 0 && rat1 <= 1) && (rat2 >= 0 && rat2 <= 1)) {
            out = start1 + (end1 - start1) * rat1;

            return true;
        }

        return false;
    }
}