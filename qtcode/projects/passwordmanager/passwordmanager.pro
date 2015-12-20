#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T18:08:29
#
#-------------------------------------------------

QT       += core gui xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = passwordmanager
TEMPLATE = app

SOURCES += \
    source/main.cpp \
    source/mainwindow.cpp \
    source/tablewidget.cpp \
    source/pwmdialog.cpp \
    source/encrypt/baseencrypt.cpp \
    source/encrypt/simplecrypt.cpp \
    source/passwordinfo.cpp \
    source/encrypt/encryptcontroller.cpp

HEADERS += \
    source/mainwindow.h \
    source/tablewidget.h \
    source/config.h \
    source/pwmdialog.h \
    source/encryptpack.h \
    source/encrypt/baseencrypt.h \
    source/encrypt/simplecrypt.h \
    source/passwordinfo.h \
    source/encrypt/encryptcontroller.h

#LIBS += -L/usr/lib/qca2 -lqca
#INCLUDEPATH += /usr/include/qca2/QtCrypto
