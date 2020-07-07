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

class TriangleShapeProperties {
public:
    using ProducedType = int;
    static const std::array<PropertyField, 3> propertyList;
};

class CircleShapeProperties {
public:
    using ProducedType = int;
    static const std::array<PropertyField, 2> propertyList;
};

template <typename T>
class ShapePropertiesModel: public QAbstractTableModel {
public:
    explicit ShapePropertiesModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;

    int columnCount(const QModelIndex &parent) const override;

    QVariant data(const QModelIndex &index, int role) const override;

    std::unordered_map<std::string, PropertyVariant> getProperties() const;
    typename T::ProducedType createFromProperties() const;

    bool setData(const QModelIndex &index, const QVariant &value, int role) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

private:
    std::vector<PropertyField> properties;
};

template<typename T>
ShapePropertiesModel<T>::ShapePropertiesModel(QObject *parent): QAbstractTableModel(parent), properties(T::propertyList.begin(), T::propertyList.end()) {
}

template<typename T>
int ShapePropertiesModel<T>::rowCount(const QModelIndex &parent) const {
    return (int) properties.size();
}

template<typename T>
int ShapePropertiesModel<T>::columnCount(const QModelIndex &parent) const {
    return 2;
}

template<typename T>
QVariant ShapePropertiesModel<T>::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= properties.size()) {
        return QVariant();
    }
    if (index.column() == 1) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return getPropertyOutput(properties[index.row()].value);
        }
    } else {
        if (role == Qt::DisplayRole) {
            return QString::fromStdString(properties[index.row()].name);
        }
    }
    return QVariant();
}

template<typename T>
bool ShapePropertiesModel<T>::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole && index.column() == 1 && index.row() < properties.size()) {

        if (!updatePropertyFromQVariant(properties[index.row()].value, value)) return false;
        std::cout << "Doing";
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

template<typename T>
Qt::ItemFlags ShapePropertiesModel<T>::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }
    return QAbstractTableModel::flags(index) | (index.column() == 1 ? Qt::ItemIsEditable : 0);
}


#endif //PHYSICS_C4_SHAPEPROPERTIESMODEL_H
