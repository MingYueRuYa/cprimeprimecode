#-------------------------------------------------
#
# Project created by QtCreator 2016-06-14T23:35:53
#
#-------------------------------------------------

QT       += core gui sql widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = linyafangzhi
TEMPLATE = app

SOURCES += ../src/main.cpp \
    ../src/mainwindow.cpp \
	../src/userpath.cpp \
	../src/db/baseinfo.cpp	\
	../src/db/db.cpp	\
	../src/db/orderinfo.cpp

HEADERS  += ../src/mainwindow.h \
	../src/userpath.h \
	../src/db/baseinfo.h \
	../src/db/db.h	\
	../src/db/orderinfo.h \
    ../src/config.h

unix {
	MOC_DIR=.moc
	OBJECT_DIR=.obj
}
