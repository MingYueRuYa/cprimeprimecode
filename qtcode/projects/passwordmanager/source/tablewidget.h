
/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTableWidget>
#include <QWidget>

class TableWidget : public QTableWidget
{
    Q_OBJECT

public:
    TableWidget(QWidget *pParent = 0);

    ~TableWidget();

private:
    void InitTable();
};

#endif //TABWIDGET_H
