// object.h - the base Object class
#ifndef PHYSICS_C4_OBJECT_H
#define PHYSICS_C4_OBJECT_H

#include "physics/core.h"

namespace physics {

    class Object {
    public:
        virtual AABB getAABB() const = 0;

        // Invalidate cached data
        virtual void invalidate() = 0;

        void addForce(Vec2 force);

        void addTorque(float torque);

        // Point in global space
        void addForceAtPoint(Vec2 force, Vec2 point);

        // Simulation-stuff
        bool unmoveable{false};

        // Translational
        Vec2 pos;
        Vec2 vel;

        Vec2 force; // Per iteration

        // Rotational
        float rot; // Do we store the matrix as well?
        float angVel;
        float torque;

        float mass;
        float momentOfInertia;

        // From pos (COM) to user-prefered reference point
        Vec2 offset;
    };

}
#endif //PHYSICS_C4_OBJECT_H
