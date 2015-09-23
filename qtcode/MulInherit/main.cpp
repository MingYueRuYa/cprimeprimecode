#include <iostream>
#include <QApplication>
#include <superlabel.h>

int main(int argc, char *argv[])
{
        QApplication app(argc, argv);
        SuperLabel sb("abc");
        //sb.QLabel::windowTitle("abc");
        sb.QLabel::show();
        sb.QPushButton::show();
        return app.exec();
}

