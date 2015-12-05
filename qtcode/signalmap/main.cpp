#include <QApplication>
#include <signalmap.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QStringList list;
    list << "hellow" << "hi";
    signalmap map(list);
    map.show();
    return app.exec();
}
