#include <cmath>

#include "physics/core.h"
#include "physics/shapes/circle.h"

namespace physics {

    Circle::Circle(float radius) : radius(radius) {
        momentOfInertia = M_PI * pow(radius, 4) / 4;
    }

    AABB Circle::getAABB() const {
        Vec2 radiusOffset{radius, radius};
        return {pos - radiusOffset, pos + radiusOffset};
    }
}
