#include "physics/shapes/polygon.h"

#include <utility>
#include <iostream>
#include <algorithm>

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

    Polygon::Polygon(std::vector<Vec2> t_points, AABB aabb, Vec2 offset) : points(std::move(t_points)), aabb(aabb),
                                                                           axes(points.size() - 1) {
        // Pre-init axes
        for (size_t i = 0; i < (points.size() - 1); i++) {
            axes[i] = (points[i + 1] - points[i]).perpendicular().normalized();
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

        for (Vec2 axis: obj1.axes) {
            // For each axis, find projections and checks intersection
            Projection p1 = obj1.project(axis);
            Projection p2 = obj2.project(axis);
            if (!p1.intersects(p2)) return;
            float intersection = p1.intersection(p2);
            if (intersection < minIntersection) {
                minIntersection = intersection;
                minAxis = axis;
            }
        }

        for (Vec2 axis: obj2.axes) {
            // For each axis, find projections and checks intersection
            Projection p1 = obj1.project(axis);
            Projection p2 = obj2.project(axis);
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

std::vector<Vec2> &Polygon::transformedPoints() const {
    if (!tranformedPointsValid) {
        Mat2x2 rotMat(rot);
        for (size_t i = 0; i < points.size(); i++) {
            _transformedPoints[i] = pos + rotMat * points[i];
        }
        tranformedPointsValid = true;
    }
    return _transformedPoints;
}

Projection Polygon::project(Vec2 axis) const {
    auto &tPoints = transformedPoints();
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

    void Polygon::handle_collision_alt(Polygon &obj1, Polygon &obj2) {
        // This assumes the polygons' AABBs have already been checked

        auto obj1TPoints = obj1.transformedPoints();
        std::vector<LineSegment> obj1Edges(obj1.points.size() - 1);
        for (int i = 0; i < obj1TPoints.size() - 1; i++) {
            obj1Edges[i] = (LineSegment(obj1TPoints[i], obj1TPoints[i + 1]));
        }

        auto obj2TPoints = obj2.transformedPoints();
        std::vector<LineSegment> obj2Edges(obj2.points.size() - 1);
        for (int i = 0; i < obj2TPoints.size() - 1; i++) {
            obj2Edges[i] = (LineSegment(obj2TPoints[i], obj2TPoints[i + 1]));
        }

        std::vector<Vec2> intersections;
        std::vector<LineSegment> edgesIntersected;

        // Assumes only one edge can be intersected - will NOT work for concave bois
        LineSegment edgeIntersected;
        Polygon *polygonWithoutEdge;

        for (LineSegment edge1 : obj1Edges) {
            for (LineSegment edge2 : obj2Edges) {
                // This might be worse than this not existing, we'll have to test
                if (!edge1.aabb.intersects(edge2.aabb)) continue;

                Vec2 intersection;
                if (edge1.intersects(edge2, intersection)) {
                    intersections.push_back(intersection);

                    // The logic here is that if it's intersected twice, it's the edge being hit
                    // Definitely a better way of doing this, but I am tired
                    if (std::count(edgesIntersected.begin(), edgesIntersected.end(), edge1)) {
                        edgeIntersected = edge1;
                        polygonWithoutEdge = &obj2;
                        goto outsideFor;
                    }
                    if (std::count(edgesIntersected.begin(), edgesIntersected.end(), edge2)) {
                        edgeIntersected = edge2;
                        polygonWithoutEdge = &obj1;
                        goto outsideFor;
                    }

                    edgesIntersected.push_back(edge1);
                    edgesIntersected.push_back(edge2);
                }
            }
        }

        outsideFor:
        if (intersections.empty()) return;
        if (polygonWithoutEdge == nullptr) {
            std::cout << "On no! No edge found?" << std::endl;
            return;
        }

        std::cout << "Collision!!!!" << std::endl;
        // They did intersect!
        // I just take a mean because I have no better method as yet
        Vec2 intersection;
        for (auto &i : intersections) {
            intersection += i;
        }
        intersection /= intersections.size();

        Vec2 normal = Vec2(edgeIntersected.end.x - edgeIntersected.start.x,
                           edgeIntersected.end.y - edgeIntersected.start.y).perpendicular();
        Vec2 vel_12 = obj1.vel - obj2.vel;

        if ((intersection + normal - polygonWithoutEdge->pos).sqrMagnitude() >
            (intersection - normal - polygonWithoutEdge->pos).sqrMagnitude()) {
            // If the opposite normal is pointing more towards the centre of mass of the polygon without the edge
            // Then that is the correct normal
            normal = normal * -1;
        }

        Vec2 rPerp1 = (intersection - obj1.pos).perpendicular();
        Vec2 rPerp2 = (intersection - obj2.pos).perpendicular();

        float e = 1;
        float impulse = calculate_impulse(obj1, obj2, rPerp1, rPerp2, normal, e);

        obj1.vel = obj1.vel + normal * impulse / obj1.mass;
        obj1.angVel = obj1.angVel + (rPerp1 * (normal * impulse)) / obj1.momentOfInertia;

        obj2.vel = obj2.vel - normal * impulse / obj2.mass;
        // Assumption
        obj2.angVel = obj2.angVel - (rPerp2 * (normal * impulse)) / obj2.momentOfInertia;
    }

void Polygon::invalidate() {
    tranformedPointsValid = false;
}
}
