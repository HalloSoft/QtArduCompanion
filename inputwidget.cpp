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

void InputWidget::setEnabled(bool eneable)
{
    // TODO:
}

void InputWidget::setDigitalValue(bool on)
{
    if(on)
        ui->labeLed->setPixmap(QPixmap(":/Icons/ledgreen.png"));
    else
        ui->labeLed->setPixmap(QPixmap(":/Icons/ledgray.png"));
}
