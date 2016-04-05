#include "inputwidget.h"
#include "ui_inputwidget.h"

InputWidget::InputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InputWidget)
{
    ui->setupUi(this);
}

InputWidget::~InputWidget()
{
    delete ui;
}

void InputWidget::setEnabled(bool enable)
{
    _enabled = enable;
    ui->analogIndicator->setEnabled(_enabled);
}

void InputWidget::setMode(eMode mode)
{
     _currentMode = mode;
     if(_currentMode == mDigital)
         ui->stackedWidget->setCurrentIndex(0);
     else
         ui->stackedWidget->setCurrentIndex(1);
}

void InputWidget::setDigitalDisplayStatus(bool on)
{
    if(_currentMode == mAnalog)
        return;

    if(on)
        ui->labeLed->setPixmap(QPixmap(":/Icons/ledgreen.png"));
    else
        ui->labeLed->setPixmap(QPixmap(":/Icons/ledgray.png"));
}

void InputWidget::setAnalogDisplayStatus(quint8 value)
{
    if(_currentMode == mAnalog)
        ui->analogIndicator->setValue(value);
}
