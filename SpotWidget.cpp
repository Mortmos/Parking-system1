#include "SpotWidget.h"

SpotWidget::SpotWidget(ParkingSpot* spot, QWidget* parent) : QPushButton(parent) {
    setText(QString("%1\n%2").arg(spot->id()).arg(spotTypeToString(spot->type())));
    setFixedSize(90, 80);

    // Початковий стиль
    updateStyle(spot->id(), spot->isFree());

    // Підписка на модель
    connect(spot, &ParkingSpot::statusChanged, this, &SpotWidget::updateStyle);
}

void SpotWidget::updateStyle(int, bool isFree) {
    if (isFree) {
        setStyleSheet("background-color: #4CAF50; color: white; border-radius: 8px; font-weight: bold; border: 2px solid #388E3C;");
    } else {
        setStyleSheet("background-color: #F44336; color: white; border-radius: 8px; font-weight: bold; border: 2px solid #D32F2F;");
    }
}
