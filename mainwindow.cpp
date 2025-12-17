#include "MainWindow.h"
#include "ParkingLot.h"
#include "SpotWidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setupUI();

    // Підписка на логи
    connect(ParkingLot::instance(), &ParkingLot::logMessage, this, &MainWindow::appendLog);
}

void MainWindow::setupUI() {
    setWindowTitle("Parking System");
    resize(1000, 600);

    QWidget* centralWidget = new QWidget;
    QHBoxLayout* mainLayout = new QHBoxLayout(centralWidget);

    // --- ЛІВА ЧАСТИНА: ВІЗУАЛІЗАЦІЯ ---
    QWidget* vizWidget = new QWidget;
    QVBoxLayout* vizLayout = new QVBoxLayout(vizWidget);

    QLabel* title1 = new QLabel("<h2>🅿️ Поверх 1</h2>");
    QGridLayout* grid1 = new QGridLayout;
    QLabel* title2 = new QLabel("<h2>🅿️ Поверх 2</h2>");
    QGridLayout* grid2 = new QGridLayout;

    auto spots = ParkingLot::instance()->getAllSpots();
    for(auto spot : spots) {
        SpotWidget* w = new SpotWidget(spot);
        if(spot->id() < 200) grid1->addWidget(w, 0, spot->id());
        else grid2->addWidget(w, 0, spot->id());
    }

    vizLayout->addWidget(title1);
    vizLayout->addLayout(grid1);
    vizLayout->addSpacing(20);
    vizLayout->addWidget(title2);
    vizLayout->addLayout(grid2);
    vizLayout->addStretch();

    // --- ПРАВА ЧАСТИНА: УПРАВЛІННЯ ---
    QWidget* ctrlWidget = new QWidget;
    ctrlWidget->setFixedWidth(320);
    QVBoxLayout* ctrlLayout = new QVBoxLayout(ctrlWidget);

    // Група В'їзд
    QGroupBox* gbEntry = new QGroupBox("🚗 В'їзд");
    QVBoxLayout* lEntry = new QVBoxLayout;
    comboVehicle = new QComboBox;
    comboVehicle->addItem("Автомобіль", (int)VehicleType::Car);
    comboVehicle->addItem("Вантажівка", (int)VehicleType::Truck);
    comboVehicle->addItem("Мотоцикл", (int)VehicleType::Motorcycle);
    comboVehicle->addItem("Електрокар", (int)VehicleType::ElectricCar);
    QPushButton* btnEnter = new QPushButton("Отримати квиток");
    btnEnter->setStyleSheet("background-color: #2196F3; color: white; padding: 8px;");
    lEntry->addWidget(new QLabel("Тип транспорту:"));
    lEntry->addWidget(comboVehicle);
    lEntry->addWidget(btnEnter);
    gbEntry->setLayout(lEntry);

    // Група Виїзд
    QGroupBox* gbExit = new QGroupBox("💳 Оплата / Виїзд");
    QVBoxLayout* lExit = new QVBoxLayout;
    spinTicketId = new QSpinBox;
    spinTicketId->setRange(1000, 9999);
    QPushButton* btnPay = new QPushButton("Сплатити");
    btnPay->setStyleSheet("background-color: #FF9800; color: white; padding: 8px;");
    lExit->addWidget(new QLabel("ID Квитка:"));
    lExit->addWidget(spinTicketId);
    lExit->addWidget(btnPay);
    gbExit->setLayout(lExit);

    // Лог
    logViewer = new QTextEdit;
    logViewer->setReadOnly(true);

    ctrlLayout->addWidget(gbEntry);
    ctrlLayout->addWidget(gbExit);
    ctrlLayout->addWidget(new QLabel("Лог подій:"));
    ctrlLayout->addWidget(logViewer);

    mainLayout->addWidget(vizWidget, 2);
    mainLayout->addWidget(ctrlWidget, 1);
    setCentralWidget(centralWidget);

    connect(btnEnter, &QPushButton::clicked, this, &MainWindow::handleEntry);
    connect(btnPay, &QPushButton::clicked, this, &MainWindow::handleExit);
}

void MainWindow::handleEntry() {
    VehicleType type = (VehicleType)comboVehicle->currentData().toInt();
    Ticket* t = ParkingLot::instance()->parkVehicle(type);

    if(t) QMessageBox::information(this, "В'їзд дозволено", QString("Квиток: #%1").arg(t->id));
    else QMessageBox::warning(this, "Немає місць", "Парковка заповнена для цього типу!");
}

void MainWindow::handleExit() {
    int id = spinTicketId->value();
    double cost = ParkingLot::instance()->processPayment(id);

    if(cost >= 0) QMessageBox::information(this, "Виїзд", QString("Оплачено: %1 грн").arg(cost));
    else QMessageBox::warning(this, "Помилка", "Квиток не знайдено");
}

void MainWindow::appendLog(QString msg) {
    logViewer->append(QTime::currentTime().toString("HH:mm:ss") + " | " + msg);
}
