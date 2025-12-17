#include "ParkingLot.h"

ParkingLot* ParkingLot::instance() {
    static ParkingLot _instance;
    return &_instance;
}

ParkingLot::ParkingLot() : ticketCounter(1000) {}

void ParkingLot::setupDemoData() {
    floor1 = new ParkingFloor(1);
    floor2 = new ParkingFloor(2);
    floor1->setNext(floor2);

    // Створення місць (Floor 1: 100-104)
    globalSpots.append(new ParkingSpot(101, SpotType::Electric));
    globalSpots.append(new ParkingSpot(102, SpotType::Electric));
    globalSpots.append(new ParkingSpot(103, SpotType::Compact));
    globalSpots.append(new ParkingSpot(104, SpotType::Compact));

    // Створення місць (Floor 2: 200-204)
    globalSpots.append(new ParkingSpot(201, SpotType::Large));
    globalSpots.append(new ParkingSpot(202, SpotType::Large));
    globalSpots.append(new ParkingSpot(203, SpotType::Compact));
    globalSpots.append(new ParkingSpot(204, SpotType::Compact));

    for(auto s : globalSpots) {
        if(s->id() < 200) floor1->addSpot(s);
        else floor2->addSpot(s);
    }
}

Ticket* ParkingLot::parkVehicle(VehicleType type) {
    ParkingSpot* spot = floor1->findSpot(type);
    if (!spot) return nullptr;

    spot->occupy();
    int tId = ++ticketCounter;
    Ticket* ticket = new Ticket{tId, QDateTime::currentDateTime(), spot->id(), 10.0};
    activeTickets.insert(tId, ticket);

    emit logMessage(QString("В'їзд: Місце %1 (Поверх %2). Квиток #%3")
                        .arg(spot->id()).arg(spot->id() < 200 ? 1 : 2).arg(tId));
    return ticket;
}

double ParkingLot::processPayment(int ticketId) {
    if (!activeTickets.contains(ticketId)) return -1.0;

    Ticket* t = activeTickets.value(ticketId);
    qint64 seconds = t->entryTime.secsTo(QDateTime::currentDateTime());
    double cost = (seconds * 0.5) + t->ratePerHour;

    for(auto spot : globalSpots) {
        if(spot->id() == t->spotId) {
            spot->free();
            break;
        }
    }

    activeTickets.remove(ticketId);
    delete t;

    emit logMessage(QString("Оплата: Квиток #%1. Сума: %2 грн").arg(ticketId).arg(cost));
    return cost;
}

const QVector<ParkingSpot*>& ParkingLot::getAllSpots() const {
    return globalSpots;
}
