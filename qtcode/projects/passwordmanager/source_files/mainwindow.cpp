#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::pwmanagermainwindow)
{
    InitTableWidget();
}

MainWindow::~MainWindow()
{
}

void MainWindow::InitTableWidget()
{
    //todo init tablewdiget
    QStringList header;
    header<< "url address" << "username" << "password";
}
