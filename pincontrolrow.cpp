#include "pincontrolrow.h"

#include "inputwidget.h"
#include "outputwidget.h"

#include <QComboBox>

PinControlRow::PinControlRow(QTreeWidget *parent, quint16 pinNumber) :
    QTreeWidgetItem(parent)
{
    setText(0, QString("Pin %1").arg(pinNumber));

    _modeComboBox = new QComboBox(parent);
    _modeComboBox->addItem(tr("In"));
    _modeComboBox->addItem(tr("Out"));

    _outputWidget = new OutputWidget(parent);
    _inputWidget = new InputWidget(parent);

    if(parent)
    {
        parent->setItemWidget(this, 1, _modeComboBox);
        parent->setItemWidget(this, 2, _outputWidget);
        parent->setItemWidget(this, 3, _inputWidget);
    }

    bool isConnected = false;                                                                      Q_UNUSED(isConnected);
    isConnected = connect(_modeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setMode())); Q_ASSERT(isConnected);

}

PinControlRow::~PinControlRow()
{

}

void PinControlRow::setEnabled(bool enabled)
{
    _modeComboBox->setEnabled(enabled);
    _outputWidget->setEnabled(enabled);
    _inputWidget->setEnabled(enabled);
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

    emit changed();
}
