#include <QApplication>
#include "dirwidget.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    DirWidget dirwidget;
    dirwidget.show();
    return app.exec();
}
