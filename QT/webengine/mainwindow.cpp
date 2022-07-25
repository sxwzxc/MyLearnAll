#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWebEngineWidgets/QtWebEngineWidgets>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //ui->centralwidget->setAttribute(Qt::WA_DontCreateNativeAncestors, true);
    //ui->centralwidget->setAttribute(Qt::WA_NativeWindow, true);
    //QApplication::setAttribute(Qt::AA_NativeWindows, false);
    //ui->centralwidget->setAttribute(Qt::WA_NativeWindow, false);
    //ui->centralwidget->setAttribute(Qt::WA_NativeWindow, false);
    //this->setAttribute(Qt::WA_NativeWindow, false);
    setWindowFlag(Qt::FramelessWindowHint);
    QWebEngineView* view = new QWebEngineView(this);
    //view->setAttribute(Qt::WA_NativeWindow, true);
    QVBoxLayout *layout = new QVBoxLayout;
    QPushButton *btn1 = new QPushButton;
    //ui->layout1->addWidget(view);
    view->setFixedSize(200, 200);
    layout->addWidget(view);

    //view->setUrl(QUrl(QStringLiteral("http://www.baidu.com")));
    view->setUrl(QUrl(QString("https://security.tp-linkshop.com.cn/vippreview/UpgradeMenuList")));
}

MainWindow::~MainWindow()
{
    delete ui;
}

