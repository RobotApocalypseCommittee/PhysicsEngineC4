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

const std::array<PropertyField, 3> TriangleShapeProperties::propertyList = {PropertyField{"noot", 6},
                                        PropertyField{"zoot", "doot"},
                                        PropertyField{"Harold", 7.5f}};

const std::array<PropertyField, 2> CircleShapeProperties::propertyList = {PropertyField{"john", "knows"},
                                                                          PropertyField{"sam", "clueless"}};
