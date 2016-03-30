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
    ui->treeWidget->setColumnCount(4);
    PinControlRow *row3 = new PinControlRow(ui->treeWidget, 13);
    row3->setEnabled( true);
    PinControlRow *row4 = new PinControlRow(ui->treeWidget, 14);
    row4->setEnabled(false);

}
