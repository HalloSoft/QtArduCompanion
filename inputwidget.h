#ifndef INPUTWIDGET_H
#define INPUTWIDGET_H

#include <QWidget>

namespace Ui {
class InputWidget;
}

class InputWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InputWidget(QWidget *parent = 0);
    ~InputWidget();

    void setEnabled(bool eneable);
    void setDigitalValue(bool on);

public slots:
    void setDigitalInput(bool on);
    void setAnalogInput(quint8 value);

private:
    Ui::InputWidget *ui;
};

#endif // INPUTWIDGET_H
