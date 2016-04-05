#ifndef ARDUCONTROLWINDOW_H
#define ARDUCONTROLWINDOW_H
#include "fdevice.h"

#include <QMainWindow>

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

    void connectDisconnect();

    void displayValue(int pin, int value);
    void displayMessage(const QString &category, const QString& message);


private:
    void initialize();

    void initializeDevice();
    void initializeTreeHeaders();
    void initializeTreeWidgetRows();

    qfirmata::FDevice *_arduino {0};
    Ui::ArduControlWindow *ui;
};

#endif // ARDUCONTROLWINDOW_H
