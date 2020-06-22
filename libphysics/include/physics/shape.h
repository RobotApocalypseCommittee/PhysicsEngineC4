// shape.h - contains basic shape logic and AABB
#ifndef PHYSICS_C4_SHAPE_H
#define PHYSICS_C4_SHAPE_H

#include "core.h"

namespace physics {

    struct AABB {
        Vec2 min, max;
    };

    class Shape {
        virtual AABB getAABB() = 0;

    };
};

#endif //PHYSICS_C4_SHAPE_H
