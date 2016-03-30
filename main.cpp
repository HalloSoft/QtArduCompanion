#include <QApplication>

#include "mainwidget.h"
#include "arducontrolwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    MainWidget mainWidget;
//    mainWidget.show();

    ArduControlWindow arduController;
    arduController.show();

    return a.exec();
}
