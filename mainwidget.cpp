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
    ui->setupUi(this);

    arduino = new FDevice();
    //arduino = new FDevice("/dev/ttyACM0");
    Q_CHECK_PTR(arduino);

    bool isConnected = false; Q_UNUSED(isConnected);
    isConnected = connect(ui->buttonOn,  SIGNAL(clicked(bool)), this, SLOT(sendTestDataOn()));  Q_ASSERT(isConnected);
    isConnected = connect(ui->buttonOff, SIGNAL(clicked(bool)), this, SLOT(sendTestDataOff())); Q_ASSERT(isConnected);
    isConnected = connect(arduino,       SIGNAL(deviceReady()), this, SLOT(setReady()));        Q_ASSERT(isConnected);
    isConnected = connect(arduino, SIGNAL(messageFired(QString,QString)), this, SLOT(appendConsoleLine(QString,QString))); Q_ASSERT(isConnected);

    arduino->setDeviceName("ArduinoUno");
    arduino->connectDevice();

    QPalette palette = ui->console->palette();
    palette.setColor(QPalette::Base, Qt::black);
    ui->console->setPalette(palette);
}

MainWidget::~MainWidget()
{
    delete ui;
}

void MainWidget::appendConsoleLine(const QString &category,const QString &text)
{
    QPalette palette = ui->console->palette();
    palette.setColor(QPalette::Text, QColor(255, 127, 127));
    ui->console->setPalette(palette);

    QString line = "<B>" + category + ":&nbsp;&nbsp;" +text + "</B>" + '\n';

    ui->console->appendHtml(line);
}

void MainWidget::sendTestDataOn()
{
     appendConsoleLine("MainWidget", "Sending Testdata (On).");
     if(connectionEstablished && arduino->available())
        arduino->digitalWrite(13, 1);
     else
         appendConsoleLine("MainWidget", "Arduino not availabe");
}

void MainWidget::sendTestDataOff()
{
     appendConsoleLine("MainWidget", "Sending Testdata (Off).");
     if(connectionEstablished && arduino->available())
        arduino->digitalWrite(13, 0);
     else
         appendConsoleLine("MainWidget", "Arduino not availabe");
}

void MainWidget::setReady()
{

    qDebug() << "Initializing ports...";

    // set Modes
    arduino->pinMode(13, FDevice::PINMODE_OUTPUT);

    connectionEstablished = true;

    appendConsoleLine("MainWidget", "Succesfully initialized.");

}
