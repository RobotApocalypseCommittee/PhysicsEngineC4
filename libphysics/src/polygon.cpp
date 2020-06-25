#include "physics/shapes/polygon.h"

#include <utility>

namespace physics {

    std::shared_ptr<Polygon> Polygon::createPolygon(std::vector<Vec2> points, Vec2 reference) {
        // Assumes convex polygon, points in some order
        // Triangulates by connecting v[0] to v[2] thru v[n-2]
        // Finds centroids
        float area = 0;
        Vec2 centroidTotal;
        for (size_t i = 1; i < points.size()-1; i++) {
            Vec2 a = points[0], b = points[i], c = points[i+1];
            float triangleArea =  (a.x * b.y + a.y * c.x + b.x * c.y - c.x * b.y - c.y * a.x - a.y * b.x) / 2.0f;
            area += triangleArea;
            centroidTotal += (a + b + c) / 3;
        }
        Vec2 centroid = centroidTotal / area;

        // All points (will be) rel to COM, so 0-ing aabb fine
        AABB aabb{};
        // Readjust all points relative to centroid
        for (Vec2& p: points) {
            p -= centroid;
            if (p.x < aabb.min.x) aabb.min.x = p.x;
            if (p.y < aabb.min.y) aabb.min.y = p.y;
            if (p.x > aabb.max.x) aabb.max.x = p.x;
            if (p.y > aabb.max.y) aabb.max.y = p.y;
        }
        reference -= centroid;
        return std::make_shared<Polygon>(points, aabb, reference);
    }

    Polygon::Polygon(std::vector<Vec2> points, AABB aabb, Vec2 offset) : points(std::move(points)), aabb(aabb) {}

    AABB Polygon::getAABB() const {
        AABB globalSpaceAABB = aabb;
        globalSpaceAABB.min += pos;
        globalSpaceAABB.max += pos;
        return globalSpaceAABB;
    }
}
