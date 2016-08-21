/****************************************************************************
**
** Copyright (C) 2010-2011 Kazo Vision. (http://www.kazovision.com)
** All rights reserved.
**
****************************************************************************/

#include "quickguidewidget.h"

#include <QtGui/QPainter>

#include "mainwindow.h"

QuickGuideWidget::QuickGuideWidget(QWidget *parent, MainWindow *pMainWindow)
	: QWidget(parent)
{
	mMainWindow = pMainWindow;

	//设置半透明背景
	QPalette palette;
	palette.setColor(QPalette::Window, QColor(50, 50, 50, 100));
	setPalette(palette);
	setAutoFillBackground(true);
}

QuickGuideWidget::~QuickGuideWidget()
{
	mMainWindow = NULL;
}

void QuickGuideWidget::mousePressEvent(QMouseEvent *event)
{
	this->hide();
}

void QuickGuideWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	QPoint startpos, endpos;

	//比赛计时。
	startpos = mMainWindow->mToolBar->geometry().center();
	endpos.setX(startpos.x());
	endpos.setY(startpos.y() + 20);
	PaintBubble(painter, startpos, endpos, this->width() / 7, tr("Menu tools"));

	startpos = mMainWindow->mSearchDockWidget->geometry().center();
	startpos.setX(startpos.x());
	endpos.setX(startpos.x() + 30);
	endpos.setY(startpos.y() - 20);
	PaintBubble(painter, startpos, endpos, this->width() / 5, tr("Search Window, you can join search."));

	//订单信息
	startpos = mMainWindow->tableWidget->geometry().center();
	startpos.setX(startpos.x() - mMainWindow->tableWidget->width() / 4);
	endpos.setX(startpos.x() - 30);
	endpos.setY(startpos.y() - 20);
	PaintBubble(painter, startpos, endpos, this->width() / 7, tr("Order info."));

	//详细信息
	startpos = mMainWindow->groupBox->geometry().center();
	endpos.setX(startpos.x() + 30);
	endpos.setY(startpos.y() - 20);
	PaintBubble(painter, startpos, endpos, this->width() / 6, tr("Order detail info."));
}

void QuickGuideWidget::PaintBubble(QPainter &pPainter, const QPoint &pStartPos, const QPoint &pEndPos, int pWidth, const QString &pContents)
{
#define BUBBLE_BOUND_WIDTH 10
#define BUBBLE_BOUND_HEIGHT 6

	//用透明色绘制文字，获取文字的实际尺寸高度。
	QFont font;
	font.setPointSize(this->height() / 50);
	pPainter.setFont(font);
	pPainter.setPen(Qt::transparent);
	QRect drawrect, textrect;
	if (pEndPos.y() > pStartPos.y()) {
		drawrect = QRect(pEndPos.x() - pWidth / 2, pEndPos.y(), pWidth, 1000);
		pPainter.drawText(drawrect, Qt::AlignHCenter | Qt::TextWordWrap, pContents, &textrect);
		textrect.adjust(0, BUBBLE_BOUND_HEIGHT, 0, BUBBLE_BOUND_HEIGHT);
	}
	else {
		drawrect = QRect(pEndPos.x() - pWidth / 2, pEndPos.y(), pWidth, 1000);
		pPainter.drawText(drawrect, Qt::AlignHCenter | Qt::TextWordWrap, pContents, &textrect);
		textrect.adjust(0, -textrect.height() - BUBBLE_BOUND_HEIGHT, 0, -textrect.height() - BUBBLE_BOUND_HEIGHT);
	}

	QRect bubblerect = textrect;
	bubblerect.adjust(-BUBBLE_BOUND_WIDTH, -BUBBLE_BOUND_HEIGHT, BUBBLE_BOUND_WIDTH, BUBBLE_BOUND_HEIGHT);

	//设置颜色。
	QLinearGradient shapebrush(0, bubblerect.top(), 0, bubblerect.bottom());
	shapebrush.setColorAt(0, QColor(227, 237, 255, 200));
	shapebrush.setColorAt(1, QColor(165, 197, 255, 200));
	pPainter.setBrush(shapebrush);
	QPen shapepen(QColor(74, 126, 187, 200), 2);
	pPainter.setPen(shapepen);

	//气泡。
	QPoint polygon[7];
	polygon[0] = QPoint(pEndPos.x() + BUBBLE_BOUND_HEIGHT, pEndPos.y());
	polygon[1] = pStartPos;
	polygon[2] = QPoint(pEndPos.x() - BUBBLE_BOUND_HEIGHT, pEndPos.y());
	if (pEndPos.y() > pStartPos.y()) {
		polygon[3] = bubblerect.topLeft();
		polygon[4] = bubblerect.bottomLeft();
		polygon[5] = bubblerect.bottomRight();
		polygon[6] = bubblerect.topRight();
	}
	else {
		polygon[3] = bubblerect.bottomLeft();
		polygon[4] = bubblerect.topLeft();
		polygon[5] = bubblerect.topRight();
		polygon[6] = bubblerect.bottomRight();
	}
	pPainter.drawPolygon(polygon, 7);

	//文字内容。
	QPen textpen(QColor(36, 54, 72));
	pPainter.setPen(textpen);
	pPainter.drawText(textrect, Qt::TextWordWrap, pContents);
}

#include "moc_quickguidewidget.cpp"
