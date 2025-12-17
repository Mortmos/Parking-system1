#ifndef TICKET_H
#define TICKET_H

#include <QDateTime>

struct Ticket {
    int id;
    QDateTime entryTime;
    int spotId;
    double ratePerHour;
};

#endif // TICKET_H
