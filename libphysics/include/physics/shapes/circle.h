
#ifndef PHYSICS_C4_CIRCLE_H
#define PHYSICS_C4_CIRCLE_H

#include <physics/object.h>

namespace physics {
    class Circle : public Object {
        explicit Circle(float radius);
        float radius;

        AABB getAABB() override;
    };
}

#endif //PHYSICS_C4_CIRCLE_H
