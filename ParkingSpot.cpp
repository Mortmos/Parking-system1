#include "ParkingSpot.h"

ParkingSpot::ParkingSpot(int id, SpotType type, QObject *parent)
    : QObject(parent), m_id(id), m_type(type), m_isFree(true) {}

int ParkingSpot::id() const { return m_id; }
SpotType ParkingSpot::type() const { return m_type; }
bool ParkingSpot::isFree() const { return m_isFree; }

void ParkingSpot::occupy() {
    if (m_isFree) {
        m_isFree = false;
        emit statusChanged(m_id, m_isFree);
    }
}

void ParkingSpot::free() {
    if (!m_isFree) {
        m_isFree = true;
        emit statusChanged(m_id, m_isFree);
    }
}
