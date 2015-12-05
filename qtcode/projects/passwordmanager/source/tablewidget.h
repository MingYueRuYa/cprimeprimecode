
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

class TabWidget : public QTableWidget
{
public:
    TabWidget(QWidget *pParent);

    ~TabWidget();
private:
    void InitTable();
};

#endif //TABWIDGET_H
