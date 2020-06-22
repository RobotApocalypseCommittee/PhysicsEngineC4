//
// Created by Attoa on 22/06/2020.
//

#include <cstdio>
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

        Vec2 vel_12 = obj1.vel - obj2.vel;
        // Only works because circles
        Vec2 normal = obj1.pos - obj2.pos;

        float impulse = calculate_impulse(vel_12, normal, obj1.mass, obj2.mass, e);
        obj1.vel = obj1.vel + normal * impulse / obj1.mass;
        obj2.vel = obj2.vel - normal * impulse / obj2.mass;
    }

    float calculate_impulse(Vec2 vel_12, Vec2 normal, float mass1, float mass2, float e) {
        float numerator = (vel_12 * -(1+e)) * normal;
        float denominator = normal * (normal * (1/mass1 + 1/mass2));

        return numerator/denominator;
    }
}
