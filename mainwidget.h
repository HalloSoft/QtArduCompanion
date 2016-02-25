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
    void sendTestData();
    void start();

private:
    Ui::MainWidget *ui;

    firmatator::FDevice *arduino;
    QTimer *activeTimer;
};

#endif // MAINWIDGET_H
