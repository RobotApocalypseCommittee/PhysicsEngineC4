// collision.h - essential collision logic
#ifndef PHYSICS_C4_COLLISION_H
#define PHYSICS_C4_COLLISION_H

#include "physics/core.h"
#include "physics/shapes/circle.h"

namespace physics {
    bool circles_overlapping(const Circle& obj1, const Circle& obj2);

    void handle_circle_collision(Circle& obj1, Circle& obj2);

    float calculate_impulse(Vec2 vel_12, Vec2 normal, float mass1, float mass2, float e = 1);
}

#endif //PHYSICS_C4_COLLISION_H
