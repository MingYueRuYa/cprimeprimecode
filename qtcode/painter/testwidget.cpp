#include "testwidget.h"
#include <QPainter>

testwidget::testwidget()
{
}

void testwidget::paintEvent (QPaintEvent *pEvent)
{
    mCpt = ctcdNone;
    QRectF rectangle(10.0, 20.0,700.0, 100.0);
    QPainter painter(this);
    painter.drawRoundedRect(rectangle, 700.0 * 0.01, 700.0 * 0.02);
}
