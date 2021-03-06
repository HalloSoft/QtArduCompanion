#include "pincontrolrow.h"

#include "inputwidget.h"
#include "outputwidget.h"

#include <QComboBox>
#include <QDebug>

PinControlRow::PinControlRow(QTreeWidget *parent, quint16 pinNumber) :
    QTreeWidgetItem(parent)
{


    setText(0, QString("Pin %1").arg(pinNumber));
    _pinNumber = pinNumber;

    _modeComboBox = new QComboBox(parent);
    _modeComboBox->addItem(tr("In"));
    _modeComboBox->addItem(tr("Out"));
    _modeComboBox->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);   // TODO: Maybe not neccessary

    _outputWidget = new OutputWidget(parent);
    _outputWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);   // TODO: Maybe not neccessary


    _inputWidget = new InputWidget(parent);
    _inputWidget->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Maximum);   // TODO: Maybe not neccessary

    if(parent)
    {
        parent->setItemWidget(this, 1, _modeComboBox);
        parent->setItemWidget(this, 2, _outputWidget);
        parent->setItemWidget(this, 3, _inputWidget);
    }

    bool isConnected = false; Q_UNUSED(isConnected);
    isConnected = connect(_modeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setMode()));
    Q_ASSERT_X(isConnected, "PinControlRow", "Constructor");
    isConnected = connect(_outputWidget, SIGNAL(digitalValueChanged(bool)), this, SLOT(processOutput(bool)));
    Q_ASSERT_X(isConnected, "PinControlRow", "Constructor");

}

PinControlRow::~PinControlRow()
{

}

void PinControlRow::setEnabled(bool enabled)
{
    _isEnabled = enabled;
    _modeComboBox->setEnabled(enabled);
    _outputWidget->setEnabled(enabled);
    _inputWidget->setEnabled(enabled);
}

void PinControlRow::setAdMode(eAdMode mode)
{
    if(mode == mAnalog)
        _inputWidget->setMode(InputWidget::mAnalog);

    if(mode == mDigital)
        _inputWidget->setMode(InputWidget::mDigital);
}

void PinControlRow::setIoMode(eIoMode mode)
{
    _mode = mode;

    if(mode == mInput)
        _modeComboBox->setCurrentIndex(0);
    if(mode == mOutput)
        _modeComboBox->setCurrentIndex(1);
}

void PinControlRow::setMode()
{
    int index = _modeComboBox->currentIndex();
    switch (index)
    {
    case 0:
        setText(3, "-");
        _mode = mInput;
        break;
    case 1:
        _mode = mOutput;
        break;
    }

    emit modeChanged(_pinNumber);
}

void PinControlRow::setAnalogInputValue(quint32 value)
{
    Q_ASSERT_X(_outputWidget, "PinControlRow", "setOutputValue(quint32 value)");


    _inputWidget->setAnalogDisplayStatus(value);
}

void PinControlRow::setDigitalInputValue(bool value)
{
    Q_ASSERT_X(_outputWidget, "PinControlRow", "setOutputValue(quint32 value)");

    qDebug() << "Digital Input:" << value;

    if(value)
        _inputWidget->setDigitalDisplayStatus(true);
    else
        _inputWidget->setDigitalDisplayStatus(false);
}

void PinControlRow::processOutput(bool value)
{
    emit buttonTriggered(_pinNumber, value);
}
