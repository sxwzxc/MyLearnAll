/********************************************************************************
** Form generated from reading UI file 'getDNS.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GETDNS_H
#define UI_GETDNS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_getDNSClass
{
public:
    QWidget *centralWidget;
    QPushButton *btn;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *getDNSClass)
    {
        if (getDNSClass->objectName().isEmpty())
            getDNSClass->setObjectName(QString::fromUtf8("getDNSClass"));
        getDNSClass->resize(600, 400);
        centralWidget = new QWidget(getDNSClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        btn = new QPushButton(centralWidget);
        btn->setObjectName(QString::fromUtf8("btn"));
        btn->setGeometry(QRect(110, 70, 107, 32));
        getDNSClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(getDNSClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 30));
        getDNSClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(getDNSClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        getDNSClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(getDNSClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        getDNSClass->setStatusBar(statusBar);

        retranslateUi(getDNSClass);

        QMetaObject::connectSlotsByName(getDNSClass);
    } // setupUi

    void retranslateUi(QMainWindow *getDNSClass)
    {
        getDNSClass->setWindowTitle(QApplication::translate("getDNSClass", "getDNS", nullptr));
        btn->setText(QApplication::translate("getDNSClass", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class getDNSClass: public Ui_getDNSClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GETDNS_H
