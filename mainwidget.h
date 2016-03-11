#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>

#include "fdevice.h"

class QTimer;

namespace Ui {
class MainWidget;
}

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = 0);
    ~MainWidget();


private slots:
    void sendTestDataOn();
    void sendTestDataOff();
    void setReady();
    void appendConsoleLine(const QString& category, const QString& text);

private:
    Ui::MainWidget *ui;

    qfirmata::FDevice *arduino;
    bool connectionEstablished;
};

#endif // MAINWIDGET_H
