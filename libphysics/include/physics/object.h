// object.h - the base Object class
#ifndef PHYSICS_C4_OBJECT_H
#define PHYSICS_C4_OBJECT_H

#include "shape.h"

namespace physics {

    class Object {
        unsigned int id;
        Vec2 vel;
        float mass;
        Vec2 pos;

        virtual AABB getAABB() const;
    };

}
#endif //PHYSICS_C4_OBJECT_H
