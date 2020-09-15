#ifndef PHYSICS_C4_PROPERTIES_H
#define PHYSICS_C4_PROPERTIES_H

#include <string_view>
#include <variant>

using PropertyValue = std::variant<std::string, float, int>;

enum class PropertyFieldID {
    Mass,
    Radius
};


struct Property {
public:
    virtual void set(PropertyValue &) = 0;

    virtual bool set(const QVariant &) = 0;

    virtual PropertyValue get() const = 0;

    virtual std::string_view getName() const = 0;
};

namespace property_defs {
template<PropertyFieldID Field>
class PropertyFieldData;

template<>
struct PropertyFieldData<PropertyFieldID::Mass> {
    using Type = float;
    static constexpr auto Name = std::string_view("mass");
};

template<>
struct PropertyFieldData<PropertyFieldID::Radius> {
    using Type = float;
    static constexpr auto Name = std::string_view("radius");
};
}

template<PropertyFieldID Field>
class PropertyField : public Property {
    using FieldData = property_defs::PropertyFieldData<Field>;
    typename FieldData::Type val;
public:
    PropertyField(typename FieldData::Type t_val) : val(t_val) {} // NOLINT(google-explicit-constructor)

    void set(PropertyValue &value) override {
        val = std::get<FieldData::Type>(value);
    }

    bool set(const QVariant &value) override {
        if (value.canConvert<FieldData::Type>()) {
            val = value.value<FieldData::Type>();
            return true;
        }
        return false;
    }

    PropertyValue get() const override {
        return val;
    }

    std::string_view getName() const override {
        return FieldData::Name;
    }

    operator typename FieldData::Type() const { return val; }

    operator typename FieldData::Type &() { return val; }

};


#endif //PHYSICS_C4_PROPERTIES_H
