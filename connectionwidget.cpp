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

    initialize();
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
}

void ConnectionWidget::connectDisconnect()
{
    const QString portName = currentPortName();

    if(_arduino && _arduino->available())
        _arduino->disconnect();
    else
       _arduino->connectDevice(portName);
}

void ConnectionWidget::initialize()
{
    foreach(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
        ui->comboBox->addItem(portInfo.portName());
}
