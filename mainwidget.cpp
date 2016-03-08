#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "fdevice.h"

#include <QDebug>
#include <QTimer>

#include <QLayout>
#include <QStatusBar>

using namespace qfirmata;

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    arduino(0),
    connectionEstablished(false)
{
    arduino = new FDevice();
    //arduino = new FDevice("/dev/ttyUSB0");
    Q_CHECK_PTR(arduino);

    arduino->connectDevice();

    ui->setupUi(this);

    bool isConnected = false;                                                                   Q_UNUSED(isConnected);
    isConnected = connect(ui->buttonOn,  SIGNAL(clicked(bool)), this, SLOT(sendTestDataOn()));  Q_ASSERT(isConnected);
    isConnected = connect(ui->buttonOff, SIGNAL(clicked(bool)), this, SLOT(sendTestDataOff())); Q_ASSERT(isConnected);
    isConnected = connect(arduino,       SIGNAL(deviceReady()), this, SLOT(setReady()));        Q_ASSERT(isConnected);

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::sendTestDataOn()
{
     qDebug() << "Sending Testdata.";
     if(connectionEstablished && arduino->available())
     {
        arduino->digitalWrite(13, 1);
     }
     else
         qDebug() << "Arduino not availabe";
}

void MainWidget::sendTestDataOff()
{
     qDebug() << "Sending Testdata.";
     if(connectionEstablished && arduino->available())
     {
        arduino->digitalWrite(13, 0);
     }
     else
         qDebug() << "Arduino not availabe";
}

void MainWidget::setReady()
{

    qDebug() << "Initializing ports...";

    // set Modes
    arduino->pinMode(13, FDevice::PINMODE_OUTPUT);

    connectionEstablished = true;


    qDebug() << "Succesfully initialized.";

}
