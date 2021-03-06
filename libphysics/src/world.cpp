#include "physics/world.h"
#include "physics/collision.h"

namespace physics {

void World::addObject(std::shared_ptr<Object> o) {
    objects.push_back(std::move(o));
}

bool World::removeObject(const std::shared_ptr<Object> &o) {
    auto it = std::find(objects.begin(), objects.end(), o);

    if (it != objects.end()) {
        objects.erase(it);
        return true;
    }
    return false;
}

void World::step(float deltaTime) {
    // TODO deal with forces

    for (const std::shared_ptr<Object> &object : objects) {
        if (object->unmoveable) continue;
        //Calculate acceleration from resultant force - Newton 2
        Vec2 acceleration = object->force / object->mass + m_gravity;

        // suvat
            object->pos += object->vel * deltaTime + acceleration * deltaTime * deltaTime * 0.5f;

            // if we had accel, change velocity with v = u + at
            object->vel += acceleration * deltaTime;

            // Now for rotation
            float rotAcc = object->torque / object->momentOfInertia;

            object->rot += object->angVel * deltaTime + rotAcc * deltaTime * deltaTime * 0.5f;

            object->angVel += rotAcc * deltaTime;
        }

        // Todo make better (if possible)
        for (int i = 0; i < objects.size(); i++) {
            const std::shared_ptr<Object> obj1 = objects[i];
            for (int j = i + 1; j < objects.size(); j++) {
                const std::shared_ptr<Object> obj2 = objects[j];
                if (!obj1->getAABB().intersects(obj2->getAABB())) {
                    continue;
                }
                if (circles_overlapping(*std::dynamic_pointer_cast<const Circle>(obj1),
                                                           *std::dynamic_pointer_cast<const Circle>(obj2))) {
                    Vec2 vel_12 = obj1->vel - obj2->vel;
                    // Only true for circles
                    Vec2 normal = obj1->pos - obj2->pos;
                    if (normal * vel_12 < 0) {
                        // They are both overlapping (colliding) and they are not separating

                        printf("Collision!\n");
                        handle_circle_collision(*std::dynamic_pointer_cast<Circle>(obj1),
                                                *std::dynamic_pointer_cast<Circle>(obj2), 1);
                    }
                }
            }
        }
}

void World::setGravity(Vec2 g_acceleration) {
    m_gravity = g_acceleration;
}
}

