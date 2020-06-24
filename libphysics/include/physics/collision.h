// collision.h - essential collision logic
#ifndef PHYSICS_C4_COLLISION_H
#define PHYSICS_C4_COLLISION_H

#include "physics/core.h"
#include "physics/shapes/circle.h"

namespace physics {
    bool circles_overlapping(const Circle &obj1, const Circle &obj2);

    void handle_circle_collision(Circle &obj1, Circle &obj2, float e);

    float calculate_impulse(Object &obj1, Object &obj2, Vec2 rPerp1, Vec2 rPerp2, Vec2 normal, float e);

    float calculate_impulse(Object &obj1, Object &obj2, Vec2 rPerp1, Vec2 rPerp2, Vec2 normal);
}

#endif //PHYSICS_C4_COLLISION_H
