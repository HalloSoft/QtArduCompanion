#include "arducontrolwindow.h"
#include "ui_arducontrolwindow.h"

#include "pincontrolrow.h"

#include <QDebug>

using namespace qfirmata;

ArduControlWindow::ArduControlWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArduControlWindow)
{
    ui->setupUi(this);
    initialize();

}

ArduControlWindow::~ArduControlWindow()
{
    delete ui;
}

void ArduControlWindow::setReady()
{
     qDebug() << "Initializing ports...";
}

void ArduControlWindow::displayValue(int pin, int value)
{
    for(int i = 0; i < ui->treeWidget->topLevelItemCount(); ++i)
    {
        PinControlRow *row = dynamic_cast<PinControlRow*>(ui->treeWidget->topLevelItem(i));

        if(row && (row->pinNumber() == pin))
            row->setInputValue(value);
    }
}

void ArduControlWindow::displayMessage(const QString& category, const QString &message)
{
    QString output = QString("%1:\t%2\n").arg(category).arg(message);
    ui->console->appendHtml(QString("<b>%1</b>").arg(output));
}

void ArduControlWindow::displayPortError(QSerialPort::SerialPortError error)
{
    qDebug() << "Error:" << _arduino->deviceName() << "No" << error;
}

void ArduControlWindow::initialize()
{
    setWindowTitle(tr("Arduino Control"));

    // Layout
    ui->splitter->setStretchFactor(0, 2);
    ui->treeWidget->setMinimumWidth(500);

    initializeDevice();
    initializeTreeHeaders();
    initializeTreeWidgetRows();

    // Console
    QPalette palette = ui->console->palette();
    palette.setColor(QPalette::Base, Qt::black);
    QColor textColor(100, 255, 150);
    palette.setColor(QPalette::Text, textColor);
    ui->console->setPalette(palette);

    ui->connectionControl->setDevice(_arduino);
}

void ArduControlWindow::initializeDevice()
{
    _arduino = new FDevice();
    Q_CHECK_PTR(_arduino);

    bool isConnected = false; Q_UNUSED(isConnected);

    isConnected = connect(_arduino, SIGNAL(deviceReady()), this, SLOT(setReady()));
    Q_ASSERT_X(isConnected, "ArduControlWindow", "initializeDevice()");

    isConnected = connect(_arduino, SIGNAL(messageFired(QString,QString)), this, SLOT(displayMessage(QString,QString)));
    Q_ASSERT_X(isConnected, "ArduControlWindow", "initializeDevice()");

    isConnected = connect(_arduino, SIGNAL(error(QSerialPort::SerialPortError)), this, SLOT(displayPortError(QSerialPort::SerialPortError)));
    Q_ASSERT_X(isConnected, "ArduControlWindow", "initializeDevice()");

    _arduino->setDeviceName("ArduinoUno");
}

void ArduControlWindow::initializeTreeHeaders()
{
    QStringList headers;
    headers << tr("Pin") << tr("Pin-Mode") << tr("Output") << tr("Input");
    ui->treeWidget->setHeaderLabels(headers);

    ui->treeWidget->setColumnWidth(2, 200);
}

void ArduControlWindow::initializeTreeWidgetRows()
{
    ui->treeWidget->setColumnCount(4);
    PinControlRow *row1 = new PinControlRow(ui->treeWidget, 11);
    row1->setEnabled( false);
    PinControlRow *row2 = new PinControlRow(ui->treeWidget, 12);
    row2->setEnabled(false);
    PinControlRow *row3 = new PinControlRow(ui->treeWidget, 13);
    row3->setEnabled( true);
    PinControlRow *row4 = new PinControlRow(ui->treeWidget, 14);
    row4->setEnabled(false);

//    for(int i = 16; i <= 22; ++i)
//    {
//        PinControlRow *row = new PinControlRow(ui->treeWidget, i);
//        row->setEnabled( false);
//        row->setAdMode(PinControlRow::mAnalog);
//    }
}
