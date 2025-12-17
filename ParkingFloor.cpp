#include "ParkingFloor.h"

ParkingFloor::ParkingFloor(int floorNumber)
    : m_floorNumber(floorNumber), m_nextFloor(nullptr) {}

void ParkingFloor::addSpot(ParkingSpot* spot) {
    m_spots.append(spot);
}

void ParkingFloor::setNext(ParkingFloor* next) {
    m_nextFloor = next;
}

ParkingSpot* ParkingFloor::findSpot(VehicleType vehicle) {
    // 1. Шукаємо на цьому поверсі
    for (auto* spot : m_spots) {
        if (spot->isFree() && isCompatible(vehicle, spot->type())) {
            return spot;
        }
    }
    // 2. Передаємо далі по ланцюжку
    if (m_nextFloor) {
        return m_nextFloor->findSpot(vehicle);
    }
    return nullptr;
}

const QVector<ParkingSpot*>& ParkingFloor::spots() const {
    return m_spots;
}

bool ParkingFloor::isCompatible(VehicleType vehicle, SpotType spot) {
    switch (vehicle) {
    case VehicleType::Motorcycle:
        return (spot == SpotType::Compact || spot == SpotType::Large);
    case VehicleType::Car:
        return (spot == SpotType::Compact || spot == SpotType::Large);
    case VehicleType::Truck:
        return (spot == SpotType::Large);
    case VehicleType::ElectricCar:
        return (spot == SpotType::Electric || spot == SpotType::Large);
    }
    return false;
}
