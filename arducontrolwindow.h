#ifndef ARDUCONTROLWINDOW_H
#define ARDUCONTROLWINDOW_H

#include "fdevice.h"

#include <QMainWindow>

class PinControlRow;

namespace Ui {
class ArduControlWindow;
}

class ArduControlWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArduControlWindow(QWidget *parent = 0);
    ~ArduControlWindow();

private slots:
    void setReady();

    void displayValue(int pin, int value);
    void displayMessage(const QString &category, const QString& message);
    void displayPortError(QSerialPort::SerialPortError error);


private:
    void initialize();

    void initializeDevice();
    void initializeControls();
    void initializeTreeHeaders();
    void initializeTreeWidgetRows();

    void connectControlRow(PinControlRow* row) const;

    qfirmata::FDevice *_arduino {0};
    Ui::ArduControlWindow *ui;
};

#endif // ARDUCONTROLWINDOW_H
