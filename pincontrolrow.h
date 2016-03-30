#ifndef PINCONTROLROW_H
#define PINCONTROLROW_H

#include <QTreeWidgetItem>

class QComboBox;
class OutputWidget;
class InputWidget;

class PinControlRow : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
    enum eMode
    {
        mInput,
        mOutput
    };

public:
    PinControlRow(QTreeWidget *parent, quint16 pinNumber);
    ~PinControlRow();

    void setEnabled(bool enabled);

public slots:

signals:
    void changed();

private slots:
    void setMode();

private:
    quint16       _pinNumber {0};
    QComboBox    *_modeComboBox {0};
    OutputWidget *_outputWidget {0};
    InputWidget  *_inputWidget {0};
    eMode         _mode {mInput};
};

#endif // PINCONTROLROW_H
