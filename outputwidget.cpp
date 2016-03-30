#include "outputwidget.h"
#include "ui_outputwidget.h"

OutputWidget::OutputWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::OutputWidget)
{
    ui->setupUi(this);
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
