// core.h - vital pieces, small mathematical bits
#ifndef PHYSICS_C4_CORE_H
#define PHYSICS_C4_CORE_H

#define M_PI 3.14159265358979323846
constexpr double PI = M_PI;

namespace physics {

    struct Vec2 {
        Vec2(float x, float y);

        Vec2();

        float x, y;

        Vec2 operator+(Vec2 b) const;
        Vec2 operator-(Vec2 b) const;
        Vec2 operator *(float s) const;
        float operator *(Vec2 b) const;
        Vec2 operator /(float s) const;

        Vec2& operator +=(Vec2 b);
        Vec2 &operator-=(Vec2 b);

        Vec2 &operator/=(float s);

        float magnitude() const;
        float sqrMagnitude() const;

        Vec2 normalized() const;

        Vec2 perpendicular() const;
    };

    float distance(Vec2, Vec2);

    struct Mat2x2 {
        float a, b, c, d;
        explicit Mat2x2(float angle);
        Vec2 operator* (Vec2 v) const;
    };

    struct AABB {
        Vec2 min, max;

        bool intersects(AABB other) const;
    };

    struct Projection {
        float min, max;

        bool intersects(Projection other) const;

        float intersection(Projection other) const;
    };

    struct LineSegment {
        explicit LineSegment();

        explicit LineSegment(Vec2 inStart, Vec2 inEnd);

        bool operator==(LineSegment b) const;

        Vec2 start, end;
        AABB aabb;

        bool intersects(LineSegment other, Vec2 &intersection) const;

        bool intersects(LineSegment other) const;
    };

    bool intersection(Vec2 start1, Vec2 end1, Vec2 start2, Vec2 end2, Vec2 &out);
};

#endif //PHYSICS_C4_CORE_H
