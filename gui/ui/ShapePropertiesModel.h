#ifndef PHYSICS_C4_SHAPEPROPERTIESMODEL_H
#define PHYSICS_C4_SHAPEPROPERTIESMODEL_H
#include <QAbstractTableModel>
#include <array>
#include <variant>
#include <iostream>

using PropertyVariant = std::variant<std::string, float, int>;

QVariant getPropertyOutput(const PropertyVariant& v);
bool updatePropertyFromQVariant(PropertyVariant& variant, const QVariant &source);

struct PropertyField {
    std::string name;
    // Also determines type
    PropertyVariant value;
};

class RegularShapeProperties {
public:
    static const std::array<PropertyField, 2> propertyList;

    float radius;
    float mass;

    explicit RegularShapeProperties(std::unordered_map<std::string, PropertyVariant> properties);
};

class ShapePropertiesModel: public QAbstractTableModel {
public:

    template<typename T>
    static ShapePropertiesModel* create(QObject* parent = nullptr) {
        return new ShapePropertiesModel(parent, T::propertyList.begin(), T::propertyList.end());
    }

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    std::unordered_map<std::string, PropertyVariant> getProperties() const;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:

    template<typename Iter>
    ShapePropertiesModel(QObject *parent, Iter begin, Iter end) : QAbstractTableModel(parent),
    properties(begin, end) {};

    std::vector<PropertyField> properties;
};


#endif //PHYSICS_C4_SHAPEPROPERTIESMODEL_H
