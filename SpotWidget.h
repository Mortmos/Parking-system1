#ifndef SPOTWIDGET_H
#define SPOTWIDGET_H

#include <QPushButton>
#include "ParkingSpot.h"

class SpotWidget : public QPushButton {
    Q_OBJECT
public:
    explicit SpotWidget(ParkingSpot* spot, QWidget* parent = nullptr);

private slots:
    void updateStyle(int id, bool isFree);
};

#endif // SPOTWIDGET_H
