// core.h - vital pieces, small mathematical bits
#ifndef PHYSICS_C4_CORE_H
#define PHYSICS_C4_CORE_H

namespace physics {

    struct Vec2 {
        Vec2(float x, float y);

        float x, y;

        Vec2 operator+(Vec2 b) const;
        Vec2 operator-(Vec2 b) const;
        Vec2 operator *(float s) const;
    };

    struct Mat2x2 {
        float a, b, c, d;
    };

};

#endif //PHYSICS_C4_CORE_H
