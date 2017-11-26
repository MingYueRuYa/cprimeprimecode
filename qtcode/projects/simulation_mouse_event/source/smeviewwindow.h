/****************************************************************
 **
 **	Copyright (C) 2016 635672377@qq.com
 ** All rights reserved.
 **
 ***************************************************************/

#ifndef smeviewwindow_h

#define smeviewwindow_h

#include <QtWidgets/QWidget>
#include <QtGui/QMouseEvent>

/*! \brief smeViewWindow
    \author liushixiong (635672377@qq.com)
    \version 0.01
    \date 20016.09.01

    smeViewWindow 用于获取坐标的窗口
*/
class smeViewWindow : public QWidget
{
	Q_OBJECT

public:
	smeViewWindow(QWidget *pParent = 0);

	~smeViewWindow();

protected:
	void mousePressEvent(QMouseEvent *pMouseEvent);

	void closeEvent(QCloseEvent *pCloseEvent);

signals:
	void OnUpdatePosition(const int &pXPosition, const int &pYPosition);

};

#endif //smeviewwindow_h