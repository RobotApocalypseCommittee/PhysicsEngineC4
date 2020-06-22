// object.h - the base Object class
#ifndef PHYSICS_C4_OBJECT_H
#define PHYSICS_C4_OBJECT_H

#include "physics/core.h"

namespace physics {

    class Object {
    public:
        virtual AABB getAABB() const = 0;
        Vec2 pos;
        Vec2 vel;
        float mass;
    protected:

        unsigned int id;
    };

}
#endif //PHYSICS_C4_OBJECT_H
