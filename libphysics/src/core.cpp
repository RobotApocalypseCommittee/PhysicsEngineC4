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

    Vec2 &Vec2::operator/=(float s) {
        x /= s;
        y /= s;
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

    LineSegment::LineSegment() = default;

    LineSegment::LineSegment(Vec2 inStart, Vec2 inEnd) {
        start = inStart;
        end = inEnd;

        aabb = {{std::min(start.x, end.x), std::min(start.y, end.y)},
                {std::max(start.x, end.x), std::max(start.y, end.y)}};
    }

    bool LineSegment::intersects(LineSegment other, Vec2 &intersection) const {
        float v = (other.end.x - other.start.x) * (start.y - end.y) - (start.x - end.x) * (other.end.y - other.start.y);
        if (v == 0) {
            return false;
        }

        float rat1 = ((other.start.y - other.end.y) * (start.x - other.start.x) +
                      (other.end.x - other.start.x) * (start.y - other.start.y)) / v;
        float rat2 =
                ((start.y - end.y) * (start.x - other.start.x) + (end.x - start.x) * (start.y - other.start.y)) / v;

        if ((rat1 >= 0 && rat1 <= 1) && (rat2 >= 0 && rat2 <= 1)) {
            intersection = start + (end - start) * rat1;
            return true;
        }

        return false;
    }

    bool LineSegment::intersects(LineSegment other) const {
        Vec2 _;
        return intersects(other, _);
    }

    bool LineSegment::operator==(LineSegment b) const {
        // yes, in this case, [A, B] != [B, A] even though it sort of should
        return (start.x == b.start.x && start.y == b.start.y && end.x == b.end.x && end.y == b.end.y);
    }
}