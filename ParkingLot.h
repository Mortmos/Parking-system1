#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <QObject>
#include <QMap>
#include <QVector>
#include "ParkingFloor.h"
#include "Ticket.h"

class ParkingLot : public QObject {
    Q_OBJECT
public:
    static ParkingLot* instance();

    void setupDemoData();
    Ticket* parkVehicle(VehicleType type);
    double processPayment(int ticketId);

    const QVector<ParkingSpot*>& getAllSpots() const;

signals:
    void logMessage(QString msg);

private:
    ParkingLot(); // Private

    ParkingFloor* floor1;
    ParkingFloor* floor2;
    QVector<ParkingSpot*> globalSpots;
    QMap<int, Ticket*> activeTickets;
    int ticketCounter;
};

#endif // PARKINGLOT_H
