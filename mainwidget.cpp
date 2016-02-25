#include "mainwidget.h"
#include "ui_mainwidget.h"

#include "fdevice.h"

#include <QDebug>
#include <QTimer>

using namespace firmatator;

MainWidget::MainWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWidget),
    arduino(0)
{
    arduino = new FDevice("Com1");
    Q_CHECK_PTR(arduino);

    arduino->initialize();

    ui->setupUi(this);

    bool isConnected = false;                                                                 Q_UNUSED(isConnected);
    isConnected = connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(sendTestData())); Q_ASSERT(isConnected);
    isConnected = connect(arduino, SIGNAL(deviceReady()), this, SLOT(start()));               Q_ASSERT(isConnected);

}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::sendTestData()
{
    //arduino->s
}

void MainWidget::start()
{
    activeTimer = new QTimer(this);
    activeTimer->setInterval(1*1000);
    activeTimer->setSingleShot(false);
    connect(activeTimer, SIGNAL(timeout()), this, SLOT(step()));

    qDebug() << "Initializing ports...";

    arduino->pinMode(13, FDevice::PINMODE_OUTPUT);
    //arduino->pinMode(3, FDevice::PINMODE_OUTPUT);
    arduino->pinMode(3, FDevice::PINMODE_PWM);
    arduino->pinMode(2, FDevice::PINMODE_SERVO);

    arduino->pinMode(8, FDevice::PINMODE_INPUT);
    arduino->pinMode(9, FDevice::PINMODE_INPUT);
    arduino->pinMode(14, FDevice::PINMODE_ANALOG);

    arduino->pinMode(18, FDevice::PINMODE_I2C);
    arduino->pinMode(19, FDevice::PINMODE_I2C);

    int readcmd[] = {0x00};
    //int readbyte[] = {0x02};
    arduino->I2CConfig(0, 100);
    arduino->I2CRequest(0x70, readcmd, FDevice::I2C_MODE_READ_ONCE);
    //arduino->I2CRequest(0x70, readcmd, FDevice::I2C_MODE_READ_ONCE);

    qDebug() << "Succesfully initialized.";

    qDebug() << "Starting loop...";
    activeTimer->start();
}
