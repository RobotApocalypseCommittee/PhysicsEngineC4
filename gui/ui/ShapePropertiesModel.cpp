#include "ShapePropertiesModel.h"

#include <utility>
#include "ShapeManager.h"

QVariant getPropertyOutput(const PropertyValue &v) {
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

bool updatePropertyFromQVariant(Property &property, const QVariant &source) {
    bool ok = true;
    auto prop_val = property.get();
    if (std::holds_alternative<int>(prop_val)) {
        prop_val = source.toInt(&ok);
    } else if (std::holds_alternative<float>(prop_val)) {
        prop_val = (float) source.toDouble(&ok);
    } else {
        prop_val = source.toString().toStdString();
    }
    if (ok) property.set(prop_val);
    return ok;
}

int ShapePropertiesModel::rowCount(const QModelIndex &parent) const {
    return m_shape.properties().getCount();
}

int ShapePropertiesModel::columnCount(const QModelIndex &parent) const {
    return 2;
}

QVariant ShapePropertiesModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_shape.properties().getCount()) {
        return QVariant();
    }
    if (index.column() == 1) {
        if (role == Qt::DisplayRole || role == Qt::EditRole) {
            return getPropertyOutput(m_shape.properties().get(index.row()));
        }
    } else {
        if (role == Qt::DisplayRole) {
            return QString::fromUtf8(m_shape.properties().getName(index.row()).data());
        }
    }
    return QVariant();
}

bool ShapePropertiesModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole && index.column() == 1 &&
        index.row() < m_shape.properties().getCount()) {

        if (!m_shape.properties().set(index.row(), value)) return false;
        m_shape.updateFromProperties();
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
    return static_cast<QFlag>(QAbstractTableModel::flags(index) | (index.column() == 1 ? Qt::ItemIsEditable : 0));
}

ShapePropertiesModel::ShapePropertiesModel(QObject *parent, ShapeConstruct &construct)
        : QAbstractTableModel(parent), m_shape(construct) {}

PropertyValue Properties::get(int index) const {
    return getProperty(index).get();
}

std::string_view Properties::getName(int index) const {
    return getProperty(index).getName();
}

void Properties::set(int index, PropertyValue value) {
    getProperty(index).set(value);
}

bool Properties::set(int index, const QVariant &variant) {
    return getProperty(index).set(variant);
}

const Property &Properties::getProperty(int i) const {
    return const_cast<Properties *>(this)->getProperty(i);
}

int RegularShapeProperties::getCount() const {
    return 2;
}

Property &RegularShapeProperties::getProperty(int i) {
    std::array<Property *, 2> props = {&mass, &radius};
    return *props[i];
}
