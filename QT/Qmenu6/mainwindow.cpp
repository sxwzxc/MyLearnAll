#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>

#define IPCAPP_STYLE_NVR_MENU2 "QMenu{ background: #FFFFFF; border: 2px solid red; width: 200px;margin:2px;}" \
    "QMenu:pressed{ background: #24C400;}" \
    "QMenu::item{ font: 12px;  color: #666666; height: 24px;margin:20px;}" \
    "QMenu::item:selected{ color: #FFFFFF; background-color: #24C400;}" \
    "QMenu::separator{ height: 1px; background: #606060;}"

#define IPCAPP_STYLE_NVR_MENU "QMenu{ background: #FFFFFF; border: 2px solid red; width: 56px;}" \
    "QMenu:pressed{ background: #E5F3FF;}" \
    "QMenu::item{ font: 12px;  color: #333333; height: 24px; width: 56px; padding-left:20px;}" \
    "QMenu::item:selected{ color: #333333; background-color: #E5F3FF;}" \
    "QMenu::item:disabled{ color: #999999; background-color: #FFFFFF;}" \
    "QMenu::separator{ height: 1px; background: #606060;}" \
    "QMenu::right-arrow {image: none;}"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu menu;
    QMenu menu2("hello");
    menu.addAction("test", this, [=] {});
    menu2.addAction("test3", this, [=] {});
    menu.addMenu(&menu2);
    connect(&menu2, &QMenu::aboutToShow, [&]() {
        menu2.show();
    });
    menu.setStyleSheet(IPCAPP_STYLE_NVR_MENU);
    //menu.popup();
    //menu.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    MyMenu *pMenu = new MyMenu(this);
    pMenu->addAction("test", this, [=] {});
    QAction *newAct = new QAction(pMenu);
    newAct->setText("test2");
    QMenu *pMenu2 = new QMenu("hello", pMenu);
    pMenu2->addAction("test3", this, [=] {});
    pMenu2->addAction("test4", this, [=] {});
    pMenu2->addAction("test5", this, [=] {});
    //pMenu2->setStyleSheet(IPCAPP_STYLE_NVR_MENU);
    //newAct->setMenu(pMenu2);
    pMenu->addAction(newAct);
    pMenu->setStyleSheet(IPCAPP_STYLE_NVR_MENU);
    pMenu->addMenu(pMenu2);
    pMenu->setWindowFlag(Qt::NoDropShadowWindowHint);
    /*
    connect(pMenu2, &QMenu::hovered, [&](QAction *action) {
        QString text = action->text();
        if (action->text() == "hello")
        {
            QWidget *pwdg = new QWidget;
            pwdg->show();
        }
    });
    */
    connect(pMenu2, &QMenu::aboutToShow, [&]() {
        QWidget *pwdg = new QWidget;
        //pwdg->show();
    });

    pMenu->show();
}

MyMenu::MyMenu(QWidget *parent)
    : QMenu(parent)
{
}

MyMenu::~MyMenu()
{
}

void MyMenu::leaveEvent(QEvent * e)
{
}
