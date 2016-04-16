#include "outputwidget.h"
#include "ui_outputwidget.h"

OutputWidget::OutputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputWidget)
{
    ui->setupUi(this);

    bool isConnected = false; Q_UNUSED(isConnected);
    isConnected = connect(ui->pushButtonToggle, SIGNAL(clicked(bool)), this, SLOT(processToggleButton()));
    Q_ASSERT_X(isConnected, "OutputWidget", "Constructor");
    isConnected = connect(ui->pushButtonOn, SIGNAL(clicked(bool)), this, SLOT(processOnButton()));
    Q_ASSERT_X(isConnected, "OutputWidget", "Constructor");
    isConnected = connect(ui->pushButtonOff, SIGNAL(clicked(bool)), this, SLOT(processOffButton()));
    Q_ASSERT_X(isConnected, "OutputWidget", "Constructor");
}

OutputWidget::~OutputWidget()
{
    delete ui;
}

void OutputWidget::setEnabled(bool enable)
{
    ui->pushButtonOff->setEnabled(enable);
    ui->pushButtonOn->setEnabled(enable);
    ui->pushButtonToggle->setEnabled(enable);
}

void OutputWidget::processOnButton()
{
    emit digitalValueChanged(true);
    _isDigitalOn = true;
}

void OutputWidget::processOffButton()
{
    emit digitalValueChanged(false);
    _isDigitalOn = false;
}

void OutputWidget::processToggleButton()
{
    emit digitalValueChanged(!_isDigitalOn);
    _isDigitalOn = !_isDigitalOn;
}
