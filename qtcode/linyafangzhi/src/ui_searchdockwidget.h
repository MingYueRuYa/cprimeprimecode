/********************************************************************************
** Form generated from reading UI file 'ui_searchdockwidget.ui'
**
** Created: Sat Aug 20 20:33:36 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHDOCKWIDGET_H
#define UI_SEARCHDOCKWIDGET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchDockWidget
{
public:
    QWidget *dockWidgetContents;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *vlayout_dyework;
    QLabel *label;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *chb_dyework;
    QComboBox *combo_dyework;
    QVBoxLayout *vlayout_client;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QCheckBox *chb_clientname;
    QComboBox *combo_clientname;
    QVBoxLayout *vlayout_specifation;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout;
    QCheckBox *chb_specificationproducts;
    QComboBox *combo_specificationproducts;
    QVBoxLayout *vlayout_supplier;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QCheckBox *chb_supplier;
    QComboBox *combo_supplier;
    QPushButton *btn_search;
    QSpacerItem *verticalSpacer;

    void setupUi(QDockWidget *SearchDockWidget)
    {
        if (SearchDockWidget->objectName().isEmpty())
            SearchDockWidget->setObjectName(QString::fromUtf8("SearchDockWidget"));
        SearchDockWidget->resize(181, 388);
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        verticalLayout = new QVBoxLayout(dockWidgetContents);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        vlayout_dyework = new QVBoxLayout();
        vlayout_dyework->setObjectName(QString::fromUtf8("vlayout_dyework"));
        label = new QLabel(dockWidgetContents);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        vlayout_dyework->addWidget(label);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        chb_dyework = new QCheckBox(dockWidgetContents);
        chb_dyework->setObjectName(QString::fromUtf8("chb_dyework"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(chb_dyework->sizePolicy().hasHeightForWidth());
        chb_dyework->setSizePolicy(sizePolicy);

        horizontalLayout_3->addWidget(chb_dyework);

        combo_dyework = new QComboBox(dockWidgetContents);
        combo_dyework->setObjectName(QString::fromUtf8("combo_dyework"));
        combo_dyework->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_3->addWidget(combo_dyework);


        vlayout_dyework->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(vlayout_dyework);

        vlayout_client = new QVBoxLayout();
        vlayout_client->setObjectName(QString::fromUtf8("vlayout_client"));
        label_2 = new QLabel(dockWidgetContents);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        vlayout_client->addWidget(label_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        chb_clientname = new QCheckBox(dockWidgetContents);
        chb_clientname->setObjectName(QString::fromUtf8("chb_clientname"));
        sizePolicy.setHeightForWidth(chb_clientname->sizePolicy().hasHeightForWidth());
        chb_clientname->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(chb_clientname);

        combo_clientname = new QComboBox(dockWidgetContents);
        combo_clientname->setObjectName(QString::fromUtf8("combo_clientname"));
        combo_clientname->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_2->addWidget(combo_clientname);


        vlayout_client->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(vlayout_client);

        vlayout_specifation = new QVBoxLayout();
        vlayout_specifation->setObjectName(QString::fromUtf8("vlayout_specifation"));
        label_3 = new QLabel(dockWidgetContents);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        vlayout_specifation->addWidget(label_3);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        chb_specificationproducts = new QCheckBox(dockWidgetContents);
        chb_specificationproducts->setObjectName(QString::fromUtf8("chb_specificationproducts"));
        sizePolicy.setHeightForWidth(chb_specificationproducts->sizePolicy().hasHeightForWidth());
        chb_specificationproducts->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(chb_specificationproducts);

        combo_specificationproducts = new QComboBox(dockWidgetContents);
        combo_specificationproducts->setObjectName(QString::fromUtf8("combo_specificationproducts"));
        combo_specificationproducts->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout->addWidget(combo_specificationproducts);


        vlayout_specifation->addLayout(horizontalLayout);


        verticalLayout->addLayout(vlayout_specifation);

        vlayout_supplier = new QVBoxLayout();
        vlayout_supplier->setObjectName(QString::fromUtf8("vlayout_supplier"));
        label_4 = new QLabel(dockWidgetContents);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        vlayout_supplier->addWidget(label_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        chb_supplier = new QCheckBox(dockWidgetContents);
        chb_supplier->setObjectName(QString::fromUtf8("chb_supplier"));
        sizePolicy.setHeightForWidth(chb_supplier->sizePolicy().hasHeightForWidth());
        chb_supplier->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(chb_supplier);

        combo_supplier = new QComboBox(dockWidgetContents);
        combo_supplier->setObjectName(QString::fromUtf8("combo_supplier"));
        combo_supplier->setStyleSheet(QString::fromUtf8(""));

        horizontalLayout_4->addWidget(combo_supplier);


        vlayout_supplier->addLayout(horizontalLayout_4);


        verticalLayout->addLayout(vlayout_supplier);

        btn_search = new QPushButton(dockWidgetContents);
        btn_search->setObjectName(QString::fromUtf8("btn_search"));

        verticalLayout->addWidget(btn_search);

        verticalSpacer = new QSpacerItem(20, 120, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        SearchDockWidget->setWidget(dockWidgetContents);

        retranslateUi(SearchDockWidget);

        QMetaObject::connectSlotsByName(SearchDockWidget);
    } // setupUi

    void retranslateUi(QDockWidget *SearchDockWidget)
    {
        SearchDockWidget->setWindowTitle(QApplication::translate("SearchDockWidget", "\346\220\234\347\264\242\346\240\217", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SearchDockWidget", "\346\237\223\345\216\202", 0, QApplication::UnicodeUTF8));
        chb_dyework->setText(QString());
        label_2->setText(QApplication::translate("SearchDockWidget", "\345\256\242\346\210\267", 0, QApplication::UnicodeUTF8));
        chb_clientname->setText(QString());
        label_3->setText(QApplication::translate("SearchDockWidget", "\345\223\201\345\220\215\350\247\204\346\240\274", 0, QApplication::UnicodeUTF8));
        chb_specificationproducts->setText(QString());
        label_4->setText(QApplication::translate("SearchDockWidget", "\344\276\233\345\272\224\345\225\206", 0, QApplication::UnicodeUTF8));
        chb_supplier->setText(QString());
        btn_search->setText(QApplication::translate("SearchDockWidget", "\346\237\245\350\257\242", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SearchDockWidget: public Ui_SearchDockWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHDOCKWIDGET_H
