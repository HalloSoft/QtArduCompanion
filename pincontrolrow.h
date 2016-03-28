#ifndef PINCONTROLROW_H
#define PINCONTROLROW_H

#include <QTreeWidgetItem>

class QComboBox;

class PinControlRow : public QObject, public QTreeWidgetItem
{
    Q_OBJECT
    enum eMode
    {
        mInput,
        mOutput
    };

public:
    PinControlRow(QTreeWidget *parent, const QString& name);
    void setEnabled(bool enabled);

public slots:

signals:
    void changed();

private slots:
    void setMode();

private:
    QComboBox *_modeComboBox;
    eMode      _mode;
};

#endif // PINCONTROLROW_H
