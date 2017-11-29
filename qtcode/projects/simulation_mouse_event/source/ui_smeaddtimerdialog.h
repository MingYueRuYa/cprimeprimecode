/********************************************************************************
** Form generated from reading UI file 'ui_smeaddtimerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SMEADDTIMERDIALOG_H
#define UI_SMEADDTIMERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

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
            AddTimerDialog->setObjectName(QStringLiteral("AddTimerDialog"));
        AddTimerDialog->resize(357, 188);
        verticalLayout_3 = new QVBoxLayout(AddTimerDialog);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label = new QLabel(AddTimerDialog);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_2->addWidget(label);

        label_2 = new QLabel(AddTimerDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        label_3 = new QLabel(AddTimerDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        label_4 = new QLabel(AddTimerDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_2->addWidget(label_4);

        label_5 = new QLabel(AddTimerDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_2->addWidget(label_5);


        horizontalLayout_2->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        edt_time = new QLineEdit(AddTimerDialog);
        edt_time->setObjectName(QStringLiteral("edt_time"));

        verticalLayout->addWidget(edt_time);

        edt_interval = new QLineEdit(AddTimerDialog);
        edt_interval->setObjectName(QStringLiteral("edt_interval"));

        verticalLayout->addWidget(edt_interval);

        edt_startposition = new QLineEdit(AddTimerDialog);
        edt_startposition->setObjectName(QStringLiteral("edt_startposition"));

        verticalLayout->addWidget(edt_startposition);

        edt_endposition = new QLineEdit(AddTimerDialog);
        edt_endposition->setObjectName(QStringLiteral("edt_endposition"));

        verticalLayout->addWidget(edt_endposition);

        edt_count = new QLineEdit(AddTimerDialog);
        edt_count->setObjectName(QStringLiteral("edt_count"));

        verticalLayout->addWidget(edt_count);


        horizontalLayout_2->addLayout(verticalLayout);


        verticalLayout_3->addLayout(horizontalLayout_2);

        verticalSpacer = new QSpacerItem(20, 7, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btn_ok = new QPushButton(AddTimerDialog);
        btn_ok->setObjectName(QStringLiteral("btn_ok"));

        horizontalLayout->addWidget(btn_ok);

        btn_cancel = new QPushButton(AddTimerDialog);
        btn_cancel->setObjectName(QStringLiteral("btn_cancel"));

        horizontalLayout->addWidget(btn_cancel);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(AddTimerDialog);

        QMetaObject::connectSlotsByName(AddTimerDialog);
    } // setupUi

    void retranslateUi(QDialog *AddTimerDialog)
    {
        AddTimerDialog->setWindowTitle(QApplication::translate("AddTimerDialog", "Add Timer", Q_NULLPTR));
        label->setText(QApplication::translate("AddTimerDialog", "Time:", Q_NULLPTR));
        label_2->setText(QApplication::translate("AddTimerDialog", "Interval:", Q_NULLPTR));
        label_3->setText(QApplication::translate("AddTimerDialog", "Start Position:", Q_NULLPTR));
        label_4->setText(QApplication::translate("AddTimerDialog", "End Position:", Q_NULLPTR));
        label_5->setText(QApplication::translate("AddTimerDialog", "Count:", Q_NULLPTR));
        btn_ok->setText(QApplication::translate("AddTimerDialog", "OK", Q_NULLPTR));
        btn_cancel->setText(QApplication::translate("AddTimerDialog", "Cancel", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AddTimerDialog: public Ui_AddTimerDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SMEADDTIMERDIALOG_H
