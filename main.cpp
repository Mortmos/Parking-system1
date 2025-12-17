#include <QApplication>
#include "MainWindow.h"
#include "ParkingLot.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    ParkingLot::instance()->setupDemoData();

    MainWindow w;
    w.show();

    return a.exec();
}
