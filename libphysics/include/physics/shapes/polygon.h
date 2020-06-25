// polygon.h - an arbitrary *convex* polygon
#ifndef PHYSICS_C4_POLYGON_H
#define PHYSICS_C4_POLYGON_H

#include <memory>
#include <vector>
#include <physics/core.h>
#include <physics/object.h>

namespace physics {
    class Polygon final : public Object {
    public:
        explicit Polygon(std::vector<Vec2> points, AABB aabb, Vec2 offset);
        static std::shared_ptr<Polygon> createPolygon(std::vector<Vec2> points, Vec2 reference = {0, 0});

        AABB getAABB() const override;

    private:
        std::vector<Vec2> points;
        AABB aabb;
    };
}

#endif //PHYSICS_C4_POLYGON_H
