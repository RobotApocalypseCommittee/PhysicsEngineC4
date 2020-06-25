#include "physics/shapes/polygon.h"

#include <utility>
#include <iostream>

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

    Polygon::Polygon(std::vector<Vec2> points, AABB aabb, Vec2 offset) : points(std::move(points)), aabb(aabb), axes(points.size() - 1) {
        // Pre-init axes
        for (size_t i = 0; i < (points.size() - 1); i++) {
            axes[i] = (points[i+1] - points[i]).perpendicular().normalized();
        }
    }

    AABB Polygon::getAABB() const {
        AABB globalSpaceAABB = aabb;
        globalSpaceAABB.min += pos;
        globalSpaceAABB.max += pos;
        return globalSpaceAABB;
    }

    void Polygon::handle_collision(Polygon &obj1, Polygon &obj2) {
        float minIntersection = +INFINITY;
        Vec2 minAxis;

        auto obj1TPoints = obj1.transformedPoints();
        auto obj2TPoints = obj2.transformedPoints();

        for (Vec2 axis: obj1.axes) {
            // For each axis, find projections and checks intersection
            Projection p1 = obj1.project(obj1TPoints, axis);
            Projection p2 = obj2.project(obj2TPoints, axis);
            if (!p1.intersects(p2)) return;
            float intersection = p1.intersection(p2);
            if (intersection < minIntersection) {
                minIntersection = intersection;
                minAxis = axis;
            }
        }

        for (Vec2 axis: obj2.axes) {
            // For each axis, find projections and checks intersection
            Projection p1 = obj1.project(obj1TPoints, axis);
            Projection p2 = obj2.project(obj2TPoints, axis);
            if (!p1.intersects(p2)) return;
            float intersection = p1.intersection(p2);
            if (intersection < minIntersection) {
                minIntersection = intersection;
                minAxis = axis;
            }
        }

        std::cout << "Collision!!!!" << std::endl;
        // TODO: Find collision point.
    }

    std::vector<Vec2> Polygon::transformedPoints() const {
        Mat2x2 rotMat(rot);
        std::vector<Vec2> transformed(points.size());
        for (size_t i = 0; i < points.size(); i++) {
            transformed[i] = pos + rotMat * points[i];
        }
        return transformed;
    }

    Projection Polygon::project(std::vector<Vec2> tPoints, Vec2 axis) const {
        Projection projection{tPoints[0] * axis, tPoints[0] * axis};
        for (size_t i = 1; i < tPoints.size(); i++) {
            float mag = tPoints[i] * axis;
            if (mag < projection.min) {
                projection.min = mag;
            } else if (mag > projection.max) {
                projection.max = mag;
            }
        }
        return projection;
    }
}
