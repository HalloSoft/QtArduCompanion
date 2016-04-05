#include "connectionwidget.h"
#include "ui_connectionwidget.h"

ConnectionWidget::ConnectionWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectionWidget)
{
    ui->setupUi(this);

    bool isConnected = false; Q_UNUSED(isConnected);
    isConnected = connect(ui->buttonToggleConnect, SIGNAL(clicked()), this, SIGNAL(connectButtonPressed()));
    Q_ASSERT_X(isConnected, "ConnectionWidget", "Constructor");
}

ConnectionWidget::~ConnectionWidget()
{
    delete ui;
}
