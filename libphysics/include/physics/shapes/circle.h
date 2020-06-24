
#ifndef PHYSICS_C4_CIRCLE_H
#define PHYSICS_C4_CIRCLE_H

#include <physics/object.h>

namespace physics {
    class Circle final: public Object {
    public:
        explicit Circle(float radius);

        AABB getAABB() const override;

        float radius;

    };
}

#endif //PHYSICS_C4_CIRCLE_H
