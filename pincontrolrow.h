#ifndef PINCONTROLROW_H
#define PINCONTROLROW_H

#include <QTreeWidgetItem>

class QComboBox;
class OutputWidget;
class InputWidget;

class PinControlRow : public QObject, public QTreeWidgetItem
{
    Q_OBJECT

public:
    enum eMode { mInput, mOutput};
    enum eAdMode { mDigital, mAnalog};

    PinControlRow(QTreeWidget *parent, quint16 pinNumber);
    ~PinControlRow();

    quint16 pinNumber() const {return _pinNumber;}

    void setEnabled(bool enabled);
    void setAdMode(eAdMode mode);
    void setInputValue(quint32 value);

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
    eAdMode       _adMode {mDigital};
};

#endif // PINCONTROLROW_H
