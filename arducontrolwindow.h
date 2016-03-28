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


private:
    void initialize();

    void initializeDvice();
    void initializeTreeHeaders();
    void initializeTreeWidgetRows();

    qfirmata::FDevice *arduino;
    Ui::ArduControlWindow *ui;
};

#endif // ARDUCONTROLWINDOW_H
