//
// Created by Attoa on 22/06/2020.
//

#include "physics/collision.h"
#include "physics/object.h"

namespace physics {
    bool circles_overlapping(const Circle& obj1, const Circle& obj2) {
        // Maybe add bounding box check first?
        return distance(obj1.pos, obj2.pos) <= obj1.radius+obj2.radius;
    }

    void handle_circle_collision(Circle &obj1, Circle &obj2) {
        if (!circles_overlapping(obj1, obj2)) {
            return;
        }

        Vec2 vel_12 = obj1.vel - obj2.vel;
        // Only works because circles
        Vec2 normal = obj1.pos - obj2.pos;

        float impulse = calculate_impulse(vel_12, normal, obj1.mass, obj2.mass, 1);
        obj1.vel = obj1.vel + normal * impulse/obj1.mass;
        obj2.vel = obj2.vel - normal * impulse/obj2.mass;
    }

    float calculate_impulse(Vec2 vel_12, Vec2 normal, float mass1, float mass2, float e) {
        float numerator = (vel_12 * -(1+e)) * normal;
        float denominator = normal * (normal * (1/mass1 + 1/mass2));

        return numerator/denominator;
    }
}
