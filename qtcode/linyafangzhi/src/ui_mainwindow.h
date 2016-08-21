/********************************************************************************
** Form generated from reading UI file 'ui_mainwindow.ui'
**
** Created: Sat Aug 20 23:31:48 2016
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QTableWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_exit;
    QAction *action_export;
    QAction *action_import;
    QAction *action_quickguide;
    QAction *action_about;
    QAction *action_opensearchdialog;
    QAction *action_addorder;
    QAction *action_deleteorder;
    QAction *action_option;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_10;
    QTableWidget *tableWidget;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *edt_menfu_2;
    QLabel *label_18;
    QLabel *label_23;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *edt_clientcount;
    QLineEdit *edt_othercraftwork;
    QLineEdit *edt_greyclothsuppiler;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_7;
    QLabel *label_17;
    QLabel *label_22;
    QVBoxLayout *verticalLayout_4;
    QLineEdit *edt_price;
    QLineEdit *edt_colortextilprintprice;
    QLineEdit *edt_greyclothcount;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_8;
    QLabel *label_20;
    QLabel *label_24;
    QVBoxLayout *verticalLayout_6;
    QLineEdit *edt_processcost;
    QLineEdit *edt_gradeacount;
    QLineEdit *edt_greyclothprice;
    QVBoxLayout *verticalLayout_7;
    QLabel *label_19;
    QLabel *label_21;
    QLabel *label_25;
    QVBoxLayout *verticalLayout_8;
    QLineEdit *edt_isshangrou;
    QLineEdit *edt_gradebcount;
    QLabel *label_26;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_27;
    QLineEdit *edt_memory;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QMenu *menu_4;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(958, 564);
        action_exit = new QAction(MainWindow);
        action_exit->setObjectName(QString::fromUtf8("action_exit"));
        action_export = new QAction(MainWindow);
        action_export->setObjectName(QString::fromUtf8("action_export"));
        action_import = new QAction(MainWindow);
        action_import->setObjectName(QString::fromUtf8("action_import"));
        action_quickguide = new QAction(MainWindow);
        action_quickguide->setObjectName(QString::fromUtf8("action_quickguide"));
        action_about = new QAction(MainWindow);
        action_about->setObjectName(QString::fromUtf8("action_about"));
        action_opensearchdialog = new QAction(MainWindow);
        action_opensearchdialog->setObjectName(QString::fromUtf8("action_opensearchdialog"));
        action_addorder = new QAction(MainWindow);
        action_addorder->setObjectName(QString::fromUtf8("action_addorder"));
        action_deleteorder = new QAction(MainWindow);
        action_deleteorder->setObjectName(QString::fromUtf8("action_deleteorder"));
        action_option = new QAction(MainWindow);
        action_option->setObjectName(QString::fromUtf8("action_option"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_10 = new QVBoxLayout(centralWidget);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        tableWidget = new QTableWidget(centralWidget);
        if (tableWidget->columnCount() < 8)
            tableWidget->setColumnCount(8);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout_10->addWidget(tableWidget);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_9 = new QVBoxLayout(groupBox);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        edt_menfu_2 = new QLabel(groupBox);
        edt_menfu_2->setObjectName(QString::fromUtf8("edt_menfu_2"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(edt_menfu_2->sizePolicy().hasHeightForWidth());
        edt_menfu_2->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(edt_menfu_2);

        label_18 = new QLabel(groupBox);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_18);

        label_23 = new QLabel(groupBox);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(label_23);


        horizontalLayout->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        edt_clientcount = new QLineEdit(groupBox);
        edt_clientcount->setObjectName(QString::fromUtf8("edt_clientcount"));
        edt_clientcount->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(edt_clientcount);

        edt_othercraftwork = new QLineEdit(groupBox);
        edt_othercraftwork->setObjectName(QString::fromUtf8("edt_othercraftwork"));
        edt_othercraftwork->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(edt_othercraftwork);

        edt_greyclothsuppiler = new QLineEdit(groupBox);
        edt_greyclothsuppiler->setObjectName(QString::fromUtf8("edt_greyclothsuppiler"));
        edt_greyclothsuppiler->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_2->addWidget(edt_greyclothsuppiler);


        horizontalLayout->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_7);

        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_17);

        label_22 = new QLabel(groupBox);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(label_22);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        edt_price = new QLineEdit(groupBox);
        edt_price->setObjectName(QString::fromUtf8("edt_price"));
        edt_price->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_4->addWidget(edt_price);

        edt_colortextilprintprice = new QLineEdit(groupBox);
        edt_colortextilprintprice->setObjectName(QString::fromUtf8("edt_colortextilprintprice"));
        edt_colortextilprintprice->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_4->addWidget(edt_colortextilprintprice);

        edt_greyclothcount = new QLineEdit(groupBox);
        edt_greyclothcount->setObjectName(QString::fromUtf8("edt_greyclothcount"));
        edt_greyclothcount->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_4->addWidget(edt_greyclothcount);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);

        verticalLayout_5->addWidget(label_8);

        label_20 = new QLabel(groupBox);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy);

        verticalLayout_5->addWidget(label_20);

        label_24 = new QLabel(groupBox);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        sizePolicy.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy);

        verticalLayout_5->addWidget(label_24);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        edt_processcost = new QLineEdit(groupBox);
        edt_processcost->setObjectName(QString::fromUtf8("edt_processcost"));
        edt_processcost->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_6->addWidget(edt_processcost);

        edt_gradeacount = new QLineEdit(groupBox);
        edt_gradeacount->setObjectName(QString::fromUtf8("edt_gradeacount"));
        edt_gradeacount->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_6->addWidget(edt_gradeacount);

        edt_greyclothprice = new QLineEdit(groupBox);
        edt_greyclothprice->setObjectName(QString::fromUtf8("edt_greyclothprice"));
        edt_greyclothprice->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_6->addWidget(edt_greyclothprice);


        horizontalLayout->addLayout(verticalLayout_6);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        label_19 = new QLabel(groupBox);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);

        verticalLayout_7->addWidget(label_19);

        label_21 = new QLabel(groupBox);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy);

        verticalLayout_7->addWidget(label_21);

        label_25 = new QLabel(groupBox);
        label_25->setObjectName(QString::fromUtf8("label_25"));
        sizePolicy.setHeightForWidth(label_25->sizePolicy().hasHeightForWidth());
        label_25->setSizePolicy(sizePolicy);

        verticalLayout_7->addWidget(label_25);


        horizontalLayout->addLayout(verticalLayout_7);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        edt_isshangrou = new QLineEdit(groupBox);
        edt_isshangrou->setObjectName(QString::fromUtf8("edt_isshangrou"));
        edt_isshangrou->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_8->addWidget(edt_isshangrou);

        edt_gradebcount = new QLineEdit(groupBox);
        edt_gradebcount->setObjectName(QString::fromUtf8("edt_gradebcount"));
        edt_gradebcount->setMaximumSize(QSize(16777215, 16777215));

        verticalLayout_8->addWidget(edt_gradebcount);

        label_26 = new QLabel(groupBox);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        sizePolicy.setHeightForWidth(label_26->sizePolicy().hasHeightForWidth());
        label_26->setSizePolicy(sizePolicy);

        verticalLayout_8->addWidget(label_26);


        horizontalLayout->addLayout(verticalLayout_8);


        verticalLayout_9->addLayout(horizontalLayout);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_27 = new QLabel(groupBox);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        sizePolicy.setHeightForWidth(label_27->sizePolicy().hasHeightForWidth());
        label_27->setSizePolicy(sizePolicy);

        horizontalLayout_6->addWidget(label_27);

        edt_memory = new QLineEdit(groupBox);
        edt_memory->setObjectName(QString::fromUtf8("edt_memory"));
        edt_memory->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout_6->addWidget(edt_memory);


        verticalLayout_9->addLayout(horizontalLayout_6);


        verticalLayout_10->addWidget(groupBox);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 958, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        menu_3 = new QMenu(menuBar);
        menu_3->setObjectName(QString::fromUtf8("menu_3"));
        menu_4 = new QMenu(menuBar);
        menu_4->setObjectName(QString::fromUtf8("menu_4"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menuBar->addAction(menu_3->menuAction());
        menuBar->addAction(menu_4->menuAction());
        menu->addAction(action_exit);
        menu_2->addAction(action_export);
        menu_2->addAction(action_import);
        menu_2->addSeparator();
        menu_2->addAction(action_addorder);
        menu_2->addAction(action_deleteorder);
        menu_2->addSeparator();
        menu_2->addAction(action_opensearchdialog);
        menu_3->addAction(action_option);
        menu_4->addAction(action_quickguide);
        menu_4->addAction(action_about);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\346\236\227\344\272\232\347\272\272\347\273\207", 0, QApplication::UnicodeUTF8));
        action_exit->setText(QApplication::translate("MainWindow", "\351\200\200\345\207\272", 0, QApplication::UnicodeUTF8));
        action_export->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        action_import->setText(QApplication::translate("MainWindow", "\345\257\274\345\207\272\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8));
        action_quickguide->setText(QApplication::translate("MainWindow", "\345\277\253\351\200\237\346\214\207\345\257\274", 0, QApplication::UnicodeUTF8));
        action_about->setText(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
        action_opensearchdialog->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\220\234\347\264\242\346\240\217", 0, QApplication::UnicodeUTF8));
        action_addorder->setText(QApplication::translate("MainWindow", "\345\242\236\345\212\240\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        action_deleteorder->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244\350\256\260\345\275\225", 0, QApplication::UnicodeUTF8));
        action_option->setText(QApplication::translate("MainWindow", "\351\200\211\351\241\271", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "\347\274\226\345\217\267", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "\346\237\223\345\234\272", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("MainWindow", "\344\270\213\345\215\225\346\227\245\346\234\237", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("MainWindow", "\345\256\242\346\210\267\345\247\223\345\220\215", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("MainWindow", "\345\256\242\346\210\267\350\201\224\347\263\273\346\226\271\345\274\217", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("MainWindow", "\345\223\201\345\220\215\350\247\204\346\240\274", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("MainWindow", "\351\242\234\350\211\262", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem7 = tableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("MainWindow", "\351\227\250\345\271\205", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        edt_menfu_2->setText(QApplication::translate("MainWindow", "\345\256\242\350\246\201\346\225\260:", 0, QApplication::UnicodeUTF8));
        label_18->setText(QApplication::translate("MainWindow", "\345\205\266\344\273\226\345\267\245\350\211\272:", 0, QApplication::UnicodeUTF8));
        label_23->setText(QApplication::translate("MainWindow", "\345\235\257\345\270\203\344\276\233\345\272\224\345\225\206:", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "\345\215\225\344\273\267:", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "\346\237\223\350\211\262/\345\215\260\350\212\261\345\215\225\344\273\267:", 0, QApplication::UnicodeUTF8));
        label_22->setText(QApplication::translate("MainWindow", "\345\235\257\345\270\203\346\225\260\351\207\217:", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "\345\212\240\345\267\245\350\264\271\357\274\232", 0, QApplication::UnicodeUTF8));
        label_20->setText(QApplication::translate("MainWindow", "\346\210\220\345\223\201(\344\270\200\347\255\211):", 0, QApplication::UnicodeUTF8));
        label_24->setText(QApplication::translate("MainWindow", "\345\235\257\345\270\203\345\215\225\344\273\267\357\274\232", 0, QApplication::UnicodeUTF8));
        label_19->setText(QApplication::translate("MainWindow", "\346\230\257\345\220\246\344\270\212\346\237\224:", 0, QApplication::UnicodeUTF8));
        label_21->setText(QApplication::translate("MainWindow", "\346\254\241\345\223\201\346\225\260:", 0, QApplication::UnicodeUTF8));
        label_25->setText(QApplication::translate("MainWindow", "23", 0, QApplication::UnicodeUTF8));
        label_26->setText(QApplication::translate("MainWindow", "26", 0, QApplication::UnicodeUTF8));
        label_27->setText(QApplication::translate("MainWindow", "\345\244\207\346\263\250:           ", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\347\263\273\347\273\237", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\223\215\344\275\234", 0, QApplication::UnicodeUTF8));
        menu_3->setTitle(QApplication::translate("MainWindow", "\351\205\215\347\275\256", 0, QApplication::UnicodeUTF8));
        menu_4->setTitle(QApplication::translate("MainWindow", "\345\205\263\344\272\216", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
