// shape.h - contains basic shape logic and AABB
#ifndef PHYSICS_C4_SHAPE_H
#define PHYSICS_C4_SHAPE_H

#include "core.h"

namespace physics {

    struct AABB {
        Vec2 min, max;
    };

    class Shape {
    public:
        virtual AABB getAABB() = 0;
        virtual bool testCollision(Shape* other) = 0;

    protected:
        Vec2 position;

    };
};

#endif //PHYSICS_C4_SHAPE_H
