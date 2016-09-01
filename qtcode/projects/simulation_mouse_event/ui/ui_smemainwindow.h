/********************************************************************************
** Form generated from reading UI file 'ui_smemainwindow.ui'
**
** Created: Mon Aug 29 22:43:59 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMEMAINWINDOW_H
#define UI_SMEMAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QListWidget>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_smeMainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QListWidget *listwidget_loginfo;
    QTableWidget *tablewidget_timerinfo;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *edt_xposition;
    QLabel *label;
    QLineEdit *edt_yposition;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_start;
    QPushButton *btn_stop;
    QPushButton *btn_st;

    void setupUi(QMainWindow *smeMainWindow)
    {
        if (smeMainWindow->objectName().isEmpty())
            smeMainWindow->setObjectName(QString::fromUtf8("smeMainWindow"));
        smeMainWindow->resize(1057, 395);
        centralwidget = new QWidget(smeMainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        listwidget_loginfo = new QListWidget(centralwidget);
        listwidget_loginfo->setObjectName(QString::fromUtf8("listwidget_loginfo"));

        horizontalLayout_2->addWidget(listwidget_loginfo);

        tablewidget_timerinfo = new QTableWidget(centralwidget);
        if (tablewidget_timerinfo->columnCount() < 4)
            tablewidget_timerinfo->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tablewidget_timerinfo->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tablewidget_timerinfo->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tablewidget_timerinfo->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tablewidget_timerinfo->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        tablewidget_timerinfo->setObjectName(QString::fromUtf8("tablewidget_timerinfo"));
        tablewidget_timerinfo->setColumnCount(4);

        horizontalLayout_2->addWidget(tablewidget_timerinfo);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        edt_xposition = new QLineEdit(centralwidget);
        edt_xposition->setObjectName(QString::fromUtf8("edt_xposition"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edt_xposition->sizePolicy().hasHeightForWidth());
        edt_xposition->setSizePolicy(sizePolicy);
        edt_xposition->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(edt_xposition);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        edt_yposition = new QLineEdit(centralwidget);
        edt_yposition->setObjectName(QString::fromUtf8("edt_yposition"));
        sizePolicy.setHeightForWidth(edt_yposition->sizePolicy().hasHeightForWidth());
        edt_yposition->setSizePolicy(sizePolicy);
        edt_yposition->setMaximumSize(QSize(100, 16777215));

        horizontalLayout->addWidget(edt_yposition);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btn_start = new QPushButton(centralwidget);
        btn_start->setObjectName(QString::fromUtf8("btn_start"));

        horizontalLayout_3->addWidget(btn_start);

        btn_stop = new QPushButton(centralwidget);
        btn_stop->setObjectName(QString::fromUtf8("btn_stop"));

        horizontalLayout_3->addWidget(btn_stop);

        btn_st = new QPushButton(centralwidget);
        btn_st->setObjectName(QString::fromUtf8("btn_st"));

        horizontalLayout_3->addWidget(btn_st);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_2->addLayout(verticalLayout);

        smeMainWindow->setCentralWidget(centralwidget);

        retranslateUi(smeMainWindow);

        QMetaObject::connectSlotsByName(smeMainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *smeMainWindow)
    {
        smeMainWindow->setWindowTitle(QApplication::translate("smeMainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tablewidget_timerinfo->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("smeMainWindow", "Number", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tablewidget_timerinfo->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("smeMainWindow", "Time", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tablewidget_timerinfo->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("smeMainWindow", "Start Position", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tablewidget_timerinfo->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("smeMainWindow", "End Position", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("smeMainWindow", "-", 0, QApplication::UnicodeUTF8));
        btn_start->setText(QApplication::translate("smeMainWindow", "Start", 0, QApplication::UnicodeUTF8));
        btn_stop->setText(QApplication::translate("smeMainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        btn_st->setText(QApplication::translate("smeMainWindow", "postion", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class smeMainWindow: public Ui_smeMainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMEMAINWINDOW_H
