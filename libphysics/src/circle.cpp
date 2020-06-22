#include "physics/shapes/circle.h"
namespace physics {

    Circle::Circle(float radius): radius(radius) {}

    AABB Circle::getAABB() const {
        Vec2 radiusOffset{radius, radius};
        return {pos - radiusOffset, pos + radiusOffset};
    }
}
