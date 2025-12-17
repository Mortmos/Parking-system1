#ifndef PARKINGFLOOR_H
#define PARKINGFLOOR_H

#include <QVector>
#include "ParkingSpot.h"

class ParkingFloor {
public:
    ParkingFloor(int floorNumber);

    void addSpot(ParkingSpot* spot);
    void setNext(ParkingFloor* next);

    // Chain of Responsibility Method
    ParkingSpot* findSpot(VehicleType vehicle);

    const QVector<ParkingSpot*>& spots() const;

private:
    int m_floorNumber;
    QVector<ParkingSpot*> m_spots;
    ParkingFloor* m_nextFloor;

    bool isCompatible(VehicleType vehicle, SpotType spot);
};

#endif // PARKINGFLOOR_H
