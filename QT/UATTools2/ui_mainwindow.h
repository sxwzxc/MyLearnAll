/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btnAdd;
    QPushButton *btnMod;
    QPushButton *btnDel;
    QPushButton *btnUAT;
    QPushButton *btnWork;
    QLabel *label;
    QPushButton *btnFix;
    QPushButton *btnTest;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(696, 529);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btnAdd = new QPushButton(centralwidget);
        btnAdd->setObjectName(QString::fromUtf8("btnAdd"));
        btnAdd->setGeometry(QRect(400, 130, 221, 32));
        btnMod = new QPushButton(centralwidget);
        btnMod->setObjectName(QString::fromUtf8("btnMod"));
        btnMod->setGeometry(QRect(400, 180, 221, 32));
        btnDel = new QPushButton(centralwidget);
        btnDel->setObjectName(QString::fromUtf8("btnDel"));
        btnDel->setGeometry(QRect(380, 370, 201, 32));
        btnUAT = new QPushButton(centralwidget);
        btnUAT->setObjectName(QString::fromUtf8("btnUAT"));
        btnUAT->setGeometry(QRect(30, 130, 201, 32));
        btnWork = new QPushButton(centralwidget);
        btnWork->setObjectName(QString::fromUtf8("btnWork"));
        btnWork->setGeometry(QRect(30, 210, 201, 32));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(360, 300, 271, 71));
        btnFix = new QPushButton(centralwidget);
        btnFix->setObjectName(QString::fromUtf8("btnFix"));
        btnFix->setGeometry(QRect(240, 240, 431, 32));
        btnTest = new QPushButton(centralwidget);
        btnTest->setObjectName(QString::fromUtf8("btnTest"));
        btnTest->setGeometry(QRect(510, 420, 131, 51));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 696, 30));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btnAdd->setText(QApplication::translate("MainWindow", "\344\270\272UAT\346\267\273\345\212\240\345\206\205\347\275\221\350\203\275\345\212\233", nullptr));
        btnMod->setText(QApplication::translate("MainWindow", "\346\224\266\345\233\236\350\203\275\345\212\233", nullptr));
        btnDel->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\347\275\221\347\273\234\350\256\276\347\275\256", nullptr));
        btnUAT->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\344\270\272UAT\347\275\221\347\273\234", nullptr));
        btnWork->setText(QApplication::translate("MainWindow", "\345\210\207\346\215\242\344\270\272\345\206\205\347\275\221\347\275\221\347\273\234", nullptr));
        label->setText(QApplication::translate("MainWindow", "\350\257\267\345\260\206\345\206\205\347\275\221\347\275\221\345\215\241\346\233\264\345\220\215\344\270\272\357\274\232\344\273\245\345\244\252\347\275\221", nullptr));
        btnFix->setText(QApplication::translate("MainWindow", "\350\247\243\346\236\220\345\206\205\347\275\221\345\217\257\350\256\277\351\227\256\344\275\206UAT\344\270\213\346\227\240\346\263\225\350\256\277\351\227\256\347\232\204\347\275\221\347\253\231\357\274\210\346\232\202\346\227\240\346\225\210\357\274\211", nullptr));
        btnTest->setText(QApplication::translate("MainWindow", "\346\265\213\350\257\225\357\274\201\345\215\261\351\231\251\357\274\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
