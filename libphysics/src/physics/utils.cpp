//
// Created by Attoa on 22/06/2020.
//

#include <cmath>

#include "physics/core.h"
#include "physics/utils.h"

namespace physics {
    float calculate_distance(Vec2 pos1, Vec2 pos2) {
        return sqrt(pow(pos1.x-pos2.x, 2) + pow(pos1.y-pos2.y, 2));
    }

    Vec2 relative_velocity(Vec2 vel1, Vec2 vel2) {
        return {vel1.x-vel2.x, vel1.y-vel2.y};
    }
}
