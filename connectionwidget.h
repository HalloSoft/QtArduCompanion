#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <QWidget>

#include "fdevice.h"

using namespace qfirmata;

namespace Ui {
class ConnectionWidget;
}

class ConnectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionWidget(QWidget *parent = 0);
    ~ConnectionWidget();

    QString currentPortName() const;

     void setDevice(FDevice *device);

signals:
    void connectButtonPressed(); // TODO: Maybe eliminate
    void connectionStatusChanged();

private slots:
    void connectDisconnect();
    void displayConnectionStatus();


private:
    void initializeWidget();

    FDevice    *_arduino {0};
    Ui::ConnectionWidget *ui;
};

#endif // CONNECTIONWIDGET_H
