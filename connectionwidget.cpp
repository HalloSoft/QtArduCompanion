#include "connectionwidget.h"
#include "ui_connectionwidget.h"

#include <QSerialPortInfo>

ConnectionWidget::ConnectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionWidget)
{
    ui->setupUi(this);

    bool isConnected = false; Q_UNUSED(isConnected);
    isConnected = connect(ui->buttonToggleConnect, SIGNAL(clicked()), this, SIGNAL(connectButtonPressed()));
    Q_ASSERT_X(isConnected, "ConnectionWidget", "Constructor");
    isConnected = connect(ui->buttonToggleConnect, SIGNAL(clicked()), this, SLOT(connectDisconnect()));
    Q_ASSERT_X(isConnected, "ConnectionWidget", "Constructor");

    initializeWidget();


}

ConnectionWidget::~ConnectionWidget()
{
    delete ui;
}

QString ConnectionWidget::currentPortName() const
{
    return ui->comboBox->currentText();
}

void ConnectionWidget::setDevice(FDevice *device)
{
    _arduino = device;

    if(_arduino)
    {
        bool isConnected = false; Q_UNUSED(isConnected);
        isConnected = connect(_arduino, SIGNAL(connectionStatusChanged()),this, SLOT(displayConnectionStatus()));
        Q_ASSERT_X(isConnected, "ConnectionWidget", "setDevice()");
    }
}

void ConnectionWidget::connectDisconnect()
{
    if(!_arduino)
        return;

    const QString portName = currentPortName();

    FDevice::ConnectionStatus status = _arduino->connectionStaus();

    if(status == FDevice::Disconnected)
       _arduino->connectDevice(portName);
    else
         _arduino->disconnectDevice();
}

void ConnectionWidget::displayConnectionStatus()
{
    if(!_arduino)
        return;

    FDevice::ConnectionStatus status = _arduino->connectionStaus();

    if(status == FDevice::Disconnected)
    {
        ui->connectionMonitor->setPixmap(QPixmap("://Icons/ledgray.png"));
        ui->connectionMonitor->setToolTip(tr("Disconnected"));
        ui->comboBox->setEnabled(true);
        ui->buttonToggleConnect->setText(tr("Connect"));
    }
    if(status == FDevice::Connected)
    {
        ui->connectionMonitor->setPixmap(QPixmap("://Icons/ledyellow.png"));
        ui->connectionMonitor->setToolTip(tr("Serialport connected"));
        ui->comboBox->setEnabled(false);
        ui->buttonToggleConnect->setText(tr("Diconnect"));
    }

    if(status == FDevice::Ready)
    {
        ui->connectionMonitor->setPixmap(QPixmap(":/Icons/ledgreen.png"));
        ui->connectionMonitor->setToolTip(tr("Device connected"));
        ui->comboBox->setEnabled(false);
        ui->buttonToggleConnect->setText(tr("Diconnect"));
    }
}

void ConnectionWidget::initializeWidget()
{
    foreach(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
        ui->comboBox->addItem(portInfo.portName());

    ui->connectionMonitor->setToolTip(tr("Disconnected"));
}
