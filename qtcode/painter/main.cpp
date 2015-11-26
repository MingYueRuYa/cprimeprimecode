#include <QApplication>
#include "testwidget.h"
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    testwidget test;
    test.show();
    return app.exec();
}
