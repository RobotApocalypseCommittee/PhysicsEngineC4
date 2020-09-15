// polygon.h - an arbitrary *convex* polygon
#ifndef PHYSICS_C4_POLYGON_H
#define PHYSICS_C4_POLYGON_H

#include <memory>
#include <vector>
#include "physics/core.h"
#include "physics/object.h"
#include "physics/collision.h"

namespace physics {
    class Polygon final : public Object {
    public:
        explicit Polygon(std::vector<Vec2> points, AABB aabb, Vec2 offset);

        static std::shared_ptr<Polygon> createPolygon(std::vector<Vec2> points, Vec2 reference = {0, 0});

        AABB getAABB() const override;

        void invalidate() override;

    private:

        Projection project(Vec2 axis) const;

        std::vector<Vec2> &transformedPoints() const;

        std::vector<Vec2> points;

        // Do not use directly - use transformedPoints
        mutable std::vector<Vec2> _transformedPoints;
        std::vector<Vec2> axes;
        AABB aabb;

        mutable bool tranformedPointsValid = false;

        static void handle_collision(Polygon &obj1, Polygon &obj2);

        static void handle_collision_alt(Polygon &obj1, Polygon &obj2);
    };
}

#endif //PHYSICS_C4_POLYGON_H
