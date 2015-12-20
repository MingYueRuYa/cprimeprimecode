/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef tableWidget_h
#define tableWidget_h

#include <QtGui/QTableWidget>
#include <QtGui/QWidget>

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *pParent = 0);

    ~TableWidget();

private:
    void SetupUi();
};

#endif //tableWidget_h
