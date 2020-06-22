#include "physics/world.h"
namespace physics {

    void physics::world::addObject(const std::shared_ptr<Object>& o) {
        objects.push_back(o);
    }
}

