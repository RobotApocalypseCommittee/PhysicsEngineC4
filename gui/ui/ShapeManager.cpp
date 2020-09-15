#include "ShapeManager.h"

#include <utility>
#include <QGraphicsScene>

std::unique_ptr<ShapePropertiesModel> ShapeConstruct::createModel() {
    return std::make_unique<ShapePropertiesModel>(nullptr, *this);
}

ShapeConstruct::ShapeConstruct(std::shared_ptr<physics::World> mWorld) : m_world(std::move(mWorld)) {}

bool ShapeConstruct::isPreCreation() const {
    return m_precreation;
}

physics::Object &CircleShapeConstruct::getPhysObject() const {
    return *m_object;
}

void CircleShapeConstruct::updateFromProperties() {
    m_object->radius = m_props.radius;
    m_object->mass = m_props.mass;
    if (!m_precreation) {
        m_graphicsitem->setRect(0, 0, 2 * m_props.radius, 2 * m_props.radius);
    }
}

QGraphicsItem *CircleShapeConstruct::createInScene(QGraphicsScene &scene, QPointF pos) {
    if (m_precreation) {
        m_object->pos = {static_cast<float>(pos.x()), static_cast<float>(pos.y())};
        m_world->addObject(m_object);
        m_graphicsitem = scene.addEllipse(0, 0, 2 * m_props.radius, 2 * m_props.radius);
        m_precreation = false;
    }
    return m_graphicsitem;
}

Properties &CircleShapeConstruct::properties() {
    return m_props;
}

CircleShapeConstruct::CircleShapeConstruct(std::shared_ptr<physics::World> mWorld) : ShapeConstruct(std::move(mWorld)),
                                                                                     m_object{}, m_graphicsitem{} {
    m_object = std::make_shared<physics::Circle>(m_props.radius);
    m_object->mass = m_props.mass;
}

void CircleShapeConstruct::updateFromPhysics() {
    m_graphicsitem->setPos(m_object->pos.x, m_object->pos.y);
}

physics::Object &TriangleShapeConstruct::getPhysObject() const {
    return *m_object;
}

void TriangleShapeConstruct::updateFromProperties() {
    // Preserve position, nothing else (what did they expect?)
    auto pos = m_object->pos;
    float side = 2 * m_props.radius * cosf(PI / 6.0);
    m_object = physics::Polygon::createPolygon({{0,                     0},
                                                {side * sinf(PI / 6.0), side * cosf(PI / 6.0)},
                                                {side,                  0}},
                                               {static_cast<float>(side * (sinf(PI / 6.0) + 1) / 3.0),
                                                static_cast<float>(side * cosf(PI / 6.0) / 3.0)});
    m_object->mass = m_props.mass;
    m_object->pos = pos;
    if (!m_precreation) {
        // Update
        m_world->addObject(m_object);
        QPolygonF triShape;
        triShape << QPointF(0, 0) << QPointF(side * sinf(PI / 6.0), side * cosf(PI / 6.0)) << QPointF(side, 0);
        m_graphicsitem->setPolygon(triShape);
    }
}

Properties &TriangleShapeConstruct::properties() {
    return m_props;
}

QGraphicsItem *TriangleShapeConstruct::createInScene(QGraphicsScene &scene, QPointF pos) {
    if (m_precreation) {
        m_object->pos = {static_cast<float>(pos.x()), static_cast<float>(pos.y())};
        m_world->addObject(m_object);
        QPolygonF triShape;
        float side = 2 * m_props.radius * cosf(PI / 6.0);
        triShape << QPointF(0, 0) << QPointF(side * sinf(PI / 6.0), side * cosf(PI / 6.0)) << QPointF(side, 0);
        m_graphicsitem = scene.addPolygon(triShape);
        m_precreation = false;
    }
    return m_graphicsitem;
}

TriangleShapeConstruct::TriangleShapeConstruct(std::shared_ptr<physics::World> mWorld) : ShapeConstruct(
        std::move(mWorld)), m_object{}, m_graphicsitem{} {
    float side = 2 * m_props.radius * cosf(PI / 6.0);
    m_object = physics::Polygon::createPolygon({{0,                     0},
                                                {side * sinf(PI / 6.0), side * cosf(PI / 6.0)},
                                                {side,                  0}},
                                               {static_cast<float>(side * (sinf(PI / 6.0) + 1) / 3.0),
                                                static_cast<float>(side * cosf(PI / 6.0) / 3.0)});
    m_object->mass = m_props.mass;
}

void TriangleShapeConstruct::updateFromPhysics() {
    m_graphicsitem->setPos(m_object->pos.x, m_object->pos.y);
}
