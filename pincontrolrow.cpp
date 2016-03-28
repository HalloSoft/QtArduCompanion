#include "pincontrolrow.h"

#include <QComboBox>

PinControlRow::PinControlRow(QTreeWidget *parent, const QString &name) :
    //QObject(0),
    QTreeWidgetItem(parent)
{
    setText(0, name);

    _mode = mInput;

    _modeComboBox = new QComboBox;
    _modeComboBox->addItem(tr("In"));
    _modeComboBox->addItem(tr("Out"));

    if(parent)
    {
        parent->setItemWidget(this, 1, _modeComboBox);
    }

    bool isConnected = false;                                                                      Q_UNUSED(isConnected);
    isConnected = connect(_modeComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setMode())); Q_ASSERT(isConnected);

}

void PinControlRow::setEnabled(bool enabled)
{
    _modeComboBox->setEnabled(enabled);
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
