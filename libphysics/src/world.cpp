#include "physics/world.h"
namespace physics {

    void World::addObject(const std::shared_ptr<Object> &o) {
        objects.push_back(o);
    }

    void World::step(float deltaTime) {
        // TODO
    }
}

