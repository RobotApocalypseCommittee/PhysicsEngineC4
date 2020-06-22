//
// Created by Attoa on 22/06/2020.
//

#ifndef PHYSICS_C4_COLLISION_H
#define PHYSICS_C4_COLLISION_H

#include "core.h"
#include "shapes/circle.h"

namespace physics {
    bool circles_overlapping(Circle obj1, Circle obj2);

    void handle_circle_collision(Circle obj1, Circle obj2);

    float calculate_impulse(Vec2 vel_12, Vec2 normal, float mass1, float mass2, float e);
}

#endif //PHYSICS_C4_COLLISION_H
