//
// Created by Attoa on 22/06/2020.
//

#ifndef PHYSICS_C4_UTILS_H
#define PHYSICS_C4_UTILS_H

#include "physics/core.h"

namespace physics {
    float calculate_distance(Vec2 pos1, Vec2 pos2);
    Vec2 relative_velocity(Vec2 vel1, Vec2 vel2);
}

#endif //PHYSICS_C4_UTILS_H
