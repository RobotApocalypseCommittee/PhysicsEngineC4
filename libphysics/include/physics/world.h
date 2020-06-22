#ifndef PHYSICS_C4_WORLD_H
#define PHYSICS_C4_WORLD_H

#include <vector>
#include <memory>
#include "physics/object.h"

namespace physics {
    class world {
    public:
        void addObject(const std::shared_ptr<Object>&);
        void step(float deltaTime);
    private:
        std::vector<std::shared_ptr<Object>> objects;
    };
};


#endif //PHYSICS_C4_WORLD_H
