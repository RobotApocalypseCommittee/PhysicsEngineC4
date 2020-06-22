#ifndef PHYSICS_C4_WORLD_H
#define PHYSICS_C4_WORLD_H

#include <memory>
#include <vector>
#include "physics/object.h"

namespace physics {
    class World {
    public:
        void addObject(const std::shared_ptr<Object> &o);

        void step(float deltaTime);

    private:
        std::vector<std::shared_ptr<Object>> objects;
    };
};


#endif //PHYSICS_C4_WORLD_H
