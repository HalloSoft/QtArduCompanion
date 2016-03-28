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

void ArduControlWindow::initialize()
{
    setWindowTitle(tr("Arduino control"));

    initializeDvice();
    initializeTreeHeaders();
    initializeTreeWidgetRows();
}

void ArduControlWindow::initializeDvice()
{
    arduino = new FDevice();
    Q_CHECK_PTR(arduino);

     bool isConnected = false; Q_UNUSED(isConnected);
     isConnected = connect(arduino, SIGNAL(deviceReady()), this, SLOT(setReady())); Q_ASSERT(isConnected);

     arduino->setDeviceName("ArduinoUno");
     arduino->connectDevice();
}

void ArduControlWindow::initializeTreeHeaders()
{
    QStringList headers;
    headers << tr("Pin") << tr("Pin-Mode") << tr("Input") << tr("Output");
    ui->treeWidget->setHeaderLabels(headers);

}

void ArduControlWindow::initializeTreeWidgetRows()
{
    ui->treeWidget->setColumnCount(4);
    PinControlRow *row1 = new PinControlRow(ui->treeWidget, tr("Pin 13"));
    row1->setEnabled(false);

}
