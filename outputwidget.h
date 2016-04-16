#ifndef OUTPUTWIDGET_H
#define OUTPUTWIDGET_H

#include <QWidget>

namespace Ui {
class OutputWidget;
}

class OutputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit OutputWidget(QWidget *parent = 0);
    ~OutputWidget();

    void setEnabled(bool enable);

signals:
    void digitalValueChanged(bool on);

private slots:
    void processOnButton();
    void processOffButton();
    void processToggleButton();


private:
    Ui::OutputWidget *ui;
    bool _isDigitalOn {false};
};

#endif // OUTPUTWIDGET_H
