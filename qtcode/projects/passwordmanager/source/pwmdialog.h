/****************************************************************************
**
** Copyright (C) 2015 liushixiong. (635672377@qq.com)
** All rights reserved.
**
****************************************************************************/

#ifndef pwmdialog_h
#define pwmdialog_h

#include <QtGui/QDialog>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>

/**
  * @brief   dailog window
  * @author  liushixiong (635672377@qq.com)
  * @version 0.01
  * @date    2015/11/30
  */
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

#endif //pwmdialog_h
