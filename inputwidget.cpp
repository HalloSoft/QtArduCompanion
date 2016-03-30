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
