#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QWidget>



class testwidget : public QWidget
{
public:
    testwidget();
    typedef enum { ctcdNone, ctcdCountUp, ctcdCountDown } CptTimerCountDirection;

protected:
    void paintEvent(QPaintEvent *pEvent);
    CptTimerCountDirection mCpt;
};

#endif // TESTWIDGET_H
