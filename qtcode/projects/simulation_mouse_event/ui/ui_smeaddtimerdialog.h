/********************************************************************************
** Form generated from reading UI file 'ui_smeaddtimerdialog.ui'
**
** Created: Wed Sep 7 23:17:46 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMEADDTIMERDIALOG_H
#define UI_SMEADDTIMERDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddTimerDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QVBoxLayout *verticalLayout;
    QLineEdit *edt_time;
    QLineEdit *edt_interval;
    QLineEdit *edt_startposition;
    QLineEdit *edt_endposition;
    QLineEdit *edt_count;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btn_ok;
    QPushButton *btn_cancel;

    void setupUi(QDialog *AddTimerDialog)
    {
        if (AddTimerDialog->objectName().isEmpty())
            AddTimerDialog->setObjectName(QString::fromUtf8("AddTimerDialog"));
        AddTimerDialog->resize(357, 188);
        verticalLayout_3 = new QVBoxLayout(AddTimerDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label = new QLabel(AddTimerDialog);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(AddTimerDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(AddTimerDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(AddTimerDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(AddTimerDialog);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_2->addWidget(label_5);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        edt_time = new QLineEdit(AddTimerDialog);
        edt_time->setObjectName(QString::fromUtf8("edt_time"));

        verticalLayout->addWidget(edt_time);

        edt_interval = new QLineEdit(AddTimerDialog);
        edt_interval->setObjectName(QString::fromUtf8("edt_interval"));

        verticalLayout->addWidget(edt_interval);

        edt_startposition = new QLineEdit(AddTimerDialog);
        edt_startposition->setObjectName(QString::fromUtf8("edt_startposition"));

        verticalLayout->addWidget(edt_startposition);

        edt_endposition = new QLineEdit(AddTimerDialog);
        edt_endposition->setObjectName(QString::fromUtf8("edt_endposition"));

        verticalLayout->addWidget(edt_endposition);

        edt_count = new QLineEdit(AddTimerDialog);
        edt_count->setObjectName(QString::fromUtf8("edt_count"));

        verticalLayout->addWidget(edt_count);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_ok = new QPushButton(AddTimerDialog);
        btn_ok->setObjectName(QString::fromUtf8("btn_ok"));

        horizontalLayout->addWidget(btn_ok);

        btn_cancel = new QPushButton(AddTimerDialog);
        btn_cancel->setObjectName(QString::fromUtf8("btn_cancel"));

        horizontalLayout->addWidget(btn_cancel);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(AddTimerDialog);

        QMetaObject::connectSlotsByName(AddTimerDialog);
    } // setupUi

    void retranslateUi(QDialog *AddTimerDialog)
    {
        AddTimerDialog->setWindowTitle(QApplication::translate("AddTimerDialog", "Add Timer", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddTimerDialog", "Time:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddTimerDialog", "Interval:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("AddTimerDialog", "Start Position:", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("AddTimerDialog", "End Position:", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("AddTimerDialog", "Count:", 0, QApplication::UnicodeUTF8));
        btn_ok->setText(QApplication::translate("AddTimerDialog", "OK", 0, QApplication::UnicodeUTF8));
        btn_cancel->setText(QApplication::translate("AddTimerDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddTimerDialog: public Ui_AddTimerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMEADDTIMERDIALOG_H
