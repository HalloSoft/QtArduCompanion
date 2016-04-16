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
    enum eIoMode { mInput, mOutput};
    enum eAdMode { mDigital, mAnalog};

    PinControlRow(QTreeWidget *parent, quint16 pinNumber);
    ~PinControlRow();

    quint16 pinNumber() const {return _pinNumber;}
    bool isEnabled() const {return _isEnabled;}
    eAdMode isAnalogMode() const { return _adMode;}
    eIoMode ioMode() const { return _mode;}

    void setEnabled(bool enabled);
    void setAdMode(eAdMode mode);
    void setIoMode(eIoMode mode);
    void setAnalogInputValue(quint32 value);
    void setDigitalInputValue(bool value);

public slots:

signals:
    void modeChanged(int pinNummer);
    void buttonTriggered(int pinNummer, bool value);

private slots:
    void setMode();
    void processOutput(bool value);

private:
    quint16       _pinNumber {0};
    QComboBox    *_modeComboBox {0};
    OutputWidget *_outputWidget {0};
    InputWidget  *_inputWidget {0};
    eIoMode       _mode {mInput};
    eAdMode       _adMode {mDigital};
    bool          _isEnabled {false};
};

#endif // PINCONTROLROW_H
