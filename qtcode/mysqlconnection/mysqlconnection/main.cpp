#include <QCoreApplication>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

//    QStringList strlist = QSqlDatabase::drivers();
//    qDebug() << strlist;
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("mysql");
    db.setUserName("root");
    db.setPassword("123456");
    if (! db.open()) {
        qDebug() << "Not open mysql";
    }
    else {
        qDebug() << "Open mysql";
    }
    return a.exec();
}
