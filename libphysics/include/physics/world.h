#ifndef PHYSICS_C4_WORLD_H
#define PHYSICS_C4_WORLD_H

#include <memory>
#include <vector>
#include <array>
#include "physics/object.h"

namespace physics {
    class World {
    public:
        void addObject(std::shared_ptr<Object> o);

        bool removeObject(const std::shared_ptr<Object> &o);

        void setGravity(Vec2 g_acceleration);

        void step(float deltaTime);

        std::vector<std::shared_ptr<Object>> objects;
    private:
        Vec2 m_gravity;
    };
}


#endif //PHYSICS_C4_WORLD_H
