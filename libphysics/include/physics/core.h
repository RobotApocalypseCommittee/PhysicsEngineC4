// core.h - vital pieces, small mathematical bits
#ifndef PHYSICS_C4_CORE_H
#define PHYSICS_C4_CORE_H

#define M_PI 3.14159265358979323846

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
        Vec2& operator -=(Vec2 b);

        float magnitude() const;
        float sqrMagnitude() const;

        Vec2 normalized() const;

        Vec2 perpendicular() const;
    };

    float distance(Vec2, Vec2);

    struct Mat2x2 {
        float a, b, c, d;
    };

    struct AABB {
        Vec2 min, max;

        bool intersects(AABB other) const;
    };

};

#endif //PHYSICS_C4_CORE_H
