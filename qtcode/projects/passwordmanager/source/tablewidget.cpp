/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#include <QtGui/QHeaderView>

#include "tablewidget.h"

TableWidget::TableWidget(QWidget *pParent)
   : QTableWidget(pParent)
{
    SetupUi();
}

TableWidget::~TableWidget()
{

}

void TableWidget::SetupUi()
{
    setColumnCount(3);
    QStringList header;
    header << "url address" << "username" << "password";
    setHorizontalHeaderLabels(header);
    horizontalHeader()->setResizeMode(QHeaderView::Stretch);
}
