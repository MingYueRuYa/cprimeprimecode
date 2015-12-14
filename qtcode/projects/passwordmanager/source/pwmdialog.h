/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef PWMDIALOG_H
#define PWMDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

class PWMDialog : public QDialog
{
    Q_OBJECT

public:
    PWMDialog(QWidget *pParent = 0);

    ~PWMDialog();

protected slots:
    void DoOk();

    void DoCancel();

private:
    QLabel *mTipLabel;

    QPushButton *mOkButton;

    QPushButton *mCancelButton;

};

#endif //PWMDIALOG_H
