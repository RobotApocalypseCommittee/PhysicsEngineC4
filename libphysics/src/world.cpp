#include "physics/world.h"
#include "physics/collision.h"

namespace physics {

    void World::addObject(const std::shared_ptr<Object> &o) {
        for (const std::shared_ptr<Object> &other : objects) {
            combinations.push_back({o, other});
        }

        objects.push_back(o);
    }

    void World::step(float deltaTime) {
        // TODO deal with forces

        for (const std::shared_ptr<Object> &object : objects) {
            // if we had accel from forces, do suvat: s = ut + 1/2 at^2

            object->pos = object->pos + object->vel * deltaTime;

            // if we had accel, change velocity with v = u + at
        }

        // Todo make better (if possible)
        int objectCount = objects.size();
        int nChooseTwo = objectCount * (objectCount - 1) / 2;
        for (int i = 0; i < nChooseTwo; i++) {
            const std::shared_ptr<Object> obj1 = combinations[i][0];
            const std::shared_ptr<Object> obj2 = combinations[i][1];

            if (!(obj1 == obj2) && circles_overlapping(*std::dynamic_pointer_cast<const Circle>(obj1),
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

