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

private:
    Ui::InputWidget *ui;
};

#endif // INPUTWIDGET_H
