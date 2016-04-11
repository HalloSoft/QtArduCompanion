#ifndef CONNECTIONWIDGET_H
#define CONNECTIONWIDGET_H

#include <QWidget>

namespace Ui {
class ConnectionWidget;
}

class ConnectionWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectionWidget(QWidget *parent = 0);
    ~ConnectionWidget();

    QString currentPortName() const;

signals:
    void connectButtonPressed();

private slots:


private:
    void initialize();

    Ui::ConnectionWidget *ui;
};

#endif // CONNECTIONWIDGET_H
