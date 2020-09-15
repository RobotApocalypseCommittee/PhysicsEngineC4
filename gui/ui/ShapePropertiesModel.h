#ifndef PHYSICS_C4_SHAPEPROPERTIESMODEL_H
#define PHYSICS_C4_SHAPEPROPERTIESMODEL_H

#include <QAbstractTableModel>
#include <variant>
#include <iostream>
#include "properties.h"
#include "span.hpp"

class ShapeConstruct;

QVariant getPropertyOutput(const PropertyValue &v);


class Properties {
public:
    PropertyValue get(int index) const;

    std::string_view getName(int index) const;

    void set(int index, PropertyValue value);

    bool set(int index, const QVariant &variant);

    // I am so very very sad about this compromise
    virtual int getCount() const = 0;

protected:
    virtual Property &getProperty(int i) = 0;

    virtual const Property &getProperty(int i) const;
};

class RegularShapeProperties : public Properties {
public:
    PropertyField<PropertyFieldID::Mass> mass = 1;
    PropertyField<PropertyFieldID::Radius> radius = 1;
private:
    int getCount() const override;

    Property &getProperty(int i) override;
};

class ShapePropertiesModel: public QAbstractTableModel {
public:
    ShapePropertiesModel(QObject *parent, ShapeConstruct &construct);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    ShapeConstruct &m_shape;
};


#endif //PHYSICS_C4_SHAPEPROPERTIESMODEL_H
