#ifndef PARKINGSPOT_H
#define PARKINGSPOT_H

#include <QObject>
#include "Enums.h"

class ParkingSpot : public QObject {
    Q_OBJECT
public:
    explicit ParkingSpot(int id, SpotType type, QObject *parent = nullptr);

    int id() const;
    SpotType type() const;
    bool isFree() const;

    void occupy();
    void free();

signals:
    void statusChanged(int id, bool isFree);

private:
    int m_id;
    SpotType m_type;
    bool m_isFree;
};

#endif // PARKINGSPOT_H
