#include "ShapePropertiesModel.h"

QVariant getPropertyOutput(const PropertyVariant &v) {
    if (auto p = std::get_if<int>(&v)) {
        return QVariant(*p);
    } else if (auto p = std::get_if<float>(&v)) {
        return QVariant(*p);
    } else if (auto p = std::get_if<std::string>(&v)) {
        return QVariant(QString::fromStdString(*p));
    } else {
        // TODO: An error
        return QVariant();
    }
}

bool updatePropertyFromQVariant(PropertyVariant& variant, const QVariant &source) {
    bool ok = true;
    if (std::holds_alternative<int>(variant)) {
        variant = source.toInt(&ok);
    } else if (std::holds_alternative<float>(variant)) {
        variant = (float) source.toDouble(&ok);
    } else {
        variant = source.toString().toStdString();
    }
    return ok;
}

const std::array<PropertyField, 2> RegularShapeProperties::propertyList = { PropertyField{"radius", 1.0f},
                                                                            PropertyField{"mass", 1.0f}};

RegularShapeProperties::RegularShapeProperties(std::unordered_map<std::string, PropertyVariant> properties) {
    radius = std::get<float>(properties.at("radius"));
    mass = std::get<float>(properties.at("mass"));
}

int ShapePropertiesModel::rowCount(const QModelIndex &parent) const {
    return (int) properties.size();
}

int ShapePropertiesModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant ShapePropertiesModel::data(const QModelIndex &index, int role) const {
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

bool ShapePropertiesModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole && index.column() == 1 && index.row() < properties.size()) {

        if (!updatePropertyFromQVariant(properties[index.row()].value, value)) return false;
        std::cout << "Doing";
        emit dataChanged(index, index, {role});
        return true;
    }
    return false;
}

Qt::ItemFlags ShapePropertiesModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) {
        return Qt::ItemIsEnabled;
    }
    return QAbstractTableModel::flags(index) | (index.column() == 1 ? Qt::ItemIsEditable : 0);
}

std::unordered_map<std::string, PropertyVariant> ShapePropertiesModel::getProperties() const {
    std::unordered_map<std::string, PropertyVariant> result;
    for (auto& prop: properties) {
        result.insert(std::make_pair(prop.name, prop.value));
    }
    return result;
}