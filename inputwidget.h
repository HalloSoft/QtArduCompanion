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

    enum eMode { mDigital, mAnalog};

    explicit InputWidget(QWidget *parent = 0);
    ~InputWidget();

    void setEnabled(bool enable);
    void setMode(eMode mode);
    void setDigitalValue(bool on);

public slots:
    void setDigitalDisplayStatus(bool on);
    void setAnalogDisplayStatus(quint8 value);

private:
    Ui::InputWidget *ui;

    eMode _currentMode {mAnalog};
    bool  _enabled {false};


};

#endif // INPUTWIDGET_H
