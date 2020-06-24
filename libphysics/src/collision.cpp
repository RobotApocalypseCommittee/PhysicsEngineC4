//
// Created by Attoa on 22/06/2020.
//

#include <cmath>

#include "physics/collision.h"
#include "physics/core.h"

namespace physics {
    bool circles_overlapping(const Circle &obj1, const Circle &obj2) {
        AABB circle1_aabb = obj1.getAABB();
        AABB circle2_aabb = obj2.getAABB();

        return circle1_aabb.intersects(circle2_aabb) && distance(obj1.pos, obj2.pos) <= obj1.radius + obj2.radius;
    }

    void handle_circle_collision(Circle &obj1, Circle &obj2, float e) {
        // This assumes they ARE colliding
        // Only works because circles
        Vec2 normal = obj1.pos - obj2.pos;

        // Only an approximation if they're not truly colliding at a single point (a good one though)
        Vec2 point = obj1.pos + (obj2.pos - obj1.pos) * obj1.radius / obj2.radius;
        Vec2 rPerp1 = (point - obj1.pos).perpendicular();
        Vec2 rPerp2 = (point - obj2.pos).perpendicular();

        float impulse = calculate_impulse(obj1, obj2, rPerp1, rPerp2, normal, e);

        obj1.vel = obj1.vel + normal * impulse / obj1.mass;
        obj1.angVel = obj1.angVel + (rPerp1 * (normal * impulse)) / obj1.momentOfInertia;

        obj2.vel = obj2.vel - normal * impulse / obj2.mass;
        // Assumption
        obj2.angVel = obj2.angVel - (rPerp2 * (normal * impulse)) / obj2.momentOfInertia;
    }

    float calculate_impulse(Object &obj1, Object &obj2, Vec2 rPerp1, Vec2 rPerp2, Vec2 normal, float e) {
        Vec2 vel_12 = obj1.vel - obj2.vel;
        float numerator = (vel_12 * -(1 + e)) * normal;

        float denominator = normal * normal * (1 / obj1.mass + 1 / obj2.mass) +
                            pow(rPerp1 * normal, 2) / obj1.momentOfInertia +
                            pow(rPerp2 * normal, 2) / obj2.momentOfInertia;

        return numerator / denominator;
    }

    float calculate_impulse(Object &obj1, Object &obj2, Vec2 rPerp1, Vec2 rPerp2, Vec2 normal) {
        return calculate_impulse(obj1, obj2, rPerp1, rPerp2, normal, 1);
    }
}
