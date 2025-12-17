#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QSpinBox>
#include <QTextEdit>

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void handleEntry();
    void handleExit();
    void appendLog(QString msg);

private:
    void setupUI();

    QComboBox* comboVehicle;
    QSpinBox* spinTicketId;
    QTextEdit* logViewer;
};

#endif // MAINWINDOW_H
