#include "physics/object.h"
namespace physics {

    void Object::addForce(Vec2 force) {
        this->force += force;
    }

    void Object::addTorque(float torque) {
        this->torque += torque;
    }

    void Object::addForceAtPoint(Vec2 force, Vec2 point) {
        this->addForce(force);
        Vec2 pointRelative = point - pos;
        // Dot product of 'perpendicular distance' & force
        this->addTorque(pointRelative.perpendicular() * force);
    }
}
