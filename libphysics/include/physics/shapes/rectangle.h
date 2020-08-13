// rectangle.h - An axis-aligned rectangle shape
#ifndef PHYSICS_C4_RECTANGLE_H
#define PHYSICS_C4_RECTANGLE_H

#include <physics/object.h>

namespace physics {
    class Rectangle : public Object {
    public:
        Rectangle(float height, float width);

        AABB getAABB() const override;

    private:
        float height, width;
    };
}

#endif //PHYSICS_C4_RECTANGLE_H
