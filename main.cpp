#include <QApplication>

#include "mainwidget.h"
#include "arducontrolwindow.h"

#define TEST_WITH_OLD_UI 0

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

#if (TEST_WITH_OLD_UI == 1)
    MainWidget mainWidget;
    mainWidget.show();
#else
    ArduControlWindow arduController;
    arduController.show();
#endif
    return a.exec();
}
