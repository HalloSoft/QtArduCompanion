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

void ConnectionWidget::initialize()
{
    foreach(QSerialPortInfo portInfo, QSerialPortInfo::availablePorts())
        ui->comboBox->addItem(portInfo.portName());
}
