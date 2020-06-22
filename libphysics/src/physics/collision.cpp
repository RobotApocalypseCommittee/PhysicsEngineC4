//
// Created by Attoa on 22/06/2020.
//

#include "physics/collision.h"
#include "physics/object.h"
#include "physics/utils.h"

namespace physics {
    bool circles_overlapping(Circle obj1, Circle obj2) {
        return calculate_distance(obj1.pos, obj2.pos) <= obj1.radius+obj2.radius;
    }
}
