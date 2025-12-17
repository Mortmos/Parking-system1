#ifndef ENUMS_H
#define ENUMS_H

#include <QString>

enum class SpotType { Compact, Large, Electric, Handicapped };
enum class VehicleType { Motorcycle, Car, Truck, ElectricCar };

inline QString spotTypeToString(SpotType t) {
    switch(t) {
    case SpotType::Compact: return "Compact";
    case SpotType::Large: return "Large";
    case SpotType::Electric: return "Electric";
    case SpotType::Handicapped: return "Handicapped";
    }
    return "Unknown";
}

#endif // ENUMS_H
