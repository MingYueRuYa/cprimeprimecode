#include <QApplication>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "delegate.h"
//#include <QtGui>
void PopulateData(QTableWidget &pTable)
{
    pTable.setItem(0, 0, new QTableWidgetItem(("Alax")));
    pTable.setItem(1, 0, new QTableWidgetItem(("Alice")));
    pTable.setItem(2, 0, new QTableWidgetItem(("Mary")));
    pTable.setItem(3, 0, new QTableWidgetItem(("Tom")));

    pTable.setItem(0, 1, new QTableWidgetItem(("1800/2/3")));
    pTable.setItem(1, 1, new QTableWidgetItem(("2000/5/13")));
    pTable.setItem(2, 1, new QTableWidgetItem(("1992/7/13")));
    pTable.setItem(3, 1, new QTableWidgetItem(("1993/4/23")));

    pTable.setItem(0, 2, new QTableWidgetItem(("165")));
    pTable.setItem(1, 2, new QTableWidgetItem(("173")));
    pTable.setItem(2, 2, new QTableWidgetItem(("159")));
    pTable.setItem(3, 2, new QTableWidgetItem(("179")));

    pTable.setItem(0, 3, new QTableWidgetItem(("US")));
    pTable.setItem(1, 3, new QTableWidgetItem(("Aus")));
    pTable.setItem(2, 3, new QTableWidgetItem(("Jpa")));
    pTable.setItem(3, 3, new QTableWidgetItem(("Chi")));
}


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QTableWidget table(3, 4);
    QStringList head;
    head << "name" << "birthday" << "height" << "town";
    table.setHorizontalHeaderLabels (head);

    EditorDelegate editordelegate;
    table.setItemDelegate(&editordelegate);

    PopulateData(table);
    table.show();
    //测试 代码
    return app.exec();
}
