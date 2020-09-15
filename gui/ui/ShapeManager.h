//
// Created by Joseph on 25/08/2020.
//

#ifndef PHYSICS_C4_SHAPEMANAGER_H
#define PHYSICS_C4_SHAPEMANAGER_H


#include <physics/object.h>
#include <unordered_map>
#include <QtWidgets/QGraphicsEllipseItem>
#include <physics/shapes/circle.h>
#include <physics/shapes/polygon.h>
#include <physics/world.h>
#include "ShapePropertiesModel.h"

class ShapeConstruct {
public:
    ShapeConstruct(std::shared_ptr<physics::World> mWorld);

    virtual physics::Object &getPhysObject() const = 0;

    virtual void updateFromProperties() = 0;

    virtual Properties &properties() = 0;

    virtual QGraphicsItem *createInScene(QGraphicsScene &scene, QPointF pos) = 0;

    virtual void updateFromPhysics() = 0;

    std::unique_ptr<ShapePropertiesModel> createModel();

    bool isPreCreation() const;

protected:
    std::shared_ptr<physics::World> m_world;
    bool m_precreation{true};
};

Q_DECLARE_METATYPE(std::shared_ptr<ShapeConstruct>)

class CircleShapeConstruct : public ShapeConstruct {
public:
    explicit CircleShapeConstruct(std::shared_ptr<physics::World> mWorld);

    physics::Object &getPhysObject() const override;

    Properties &properties() override;

    QGraphicsItem *createInScene(QGraphicsScene &scene, QPointF pos) override;

    void updateFromProperties() override;

    void updateFromPhysics() override;

private:
    RegularShapeProperties m_props;
    std::shared_ptr<physics::Circle> m_object;
    QGraphicsEllipseItem *m_graphicsitem;
};

class TriangleShapeConstruct : public ShapeConstruct {
public:
    explicit TriangleShapeConstruct(std::shared_ptr<physics::World> mWorld);

    physics::Object &getPhysObject() const override;

    void updateFromProperties() override;

    Properties &properties() override;

    QGraphicsItem *createInScene(QGraphicsScene &scene, QPointF pos) override;

    void updateFromPhysics() override;

private:
    RegularShapeProperties m_props;
    std::shared_ptr<physics::Polygon> m_object;
    QGraphicsPolygonItem *m_graphicsitem;
};


#endif //PHYSICS_C4_SHAPEMANAGER_H
