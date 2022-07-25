#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeView->header()->hide();
    //qw = new QQuickWidget(this);
    //qw->move(50,50);
    //    qw->resize(500,500);
    //   //qw->setResizeMode(QQuickWidget::SizeRootObjectToView);
    //qw->setSource(QUrl::fromLocalFile("D:/learn/QT/ScrollQuick/main.qml"));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent* event)
{
    if (aaa >= 56) {
        on_pushButton_2_clicked();
        aaa = 0;
    }
    pMsgItem->setData(aaa++, Qt::UserRole + 1);
}

void MainWindow::on_pushButton_clicked()
{
    pModel_ = new QStandardItemModel;
    pModel_->insertColumns(0, 1);
    for (int i = 0; i < 20; i++) {
        pMsgItem = new QStandardItem(QString::number(i) + "--" + QDateTime::currentDateTime().toString("YYYY MM DD hh mm ss"));
        pMsgItem->setData(40, Qt::UserRole + 1);
        pModel_->appendRow(pMsgItem);
    }


    ui->treeView->setItemDelegate(new ListDelegate());
    ui->treeView->setModel(pModel_);
    update();

}


void MainWindow::on_pushButton_2_clicked()
{
    pMsgItem = new QStandardItem(QString::number(index++) + "--" + QDateTime::currentDateTime().toString("YYYY MM DD hh mm ss"));
    QStandardItem* pMsgSubItem;

    pMsgSubItem = new QStandardItem(QString::number(001) + "--" + QDateTime::currentDateTime().toString("hh mm ss"));
    pMsgSubItem->setData(40, Qt::UserRole + 1);
    //pMsgItem->appendRow(pMsgSubItem);

    pMsgItem->setData(56, Qt::UserRole + 1);
    pModel_->insertRow(0, pMsgItem);
    pModel_->removeRow(pModel_->rowCount() - 5);
    update();
}


void MainWindow::on_pushButton_3_clicked()
{
   // ui->treeView->expandAll();
    startTimer(1);
    pMsgItem->setData(aaa++, Qt::UserRole + 1);
    update();

}

