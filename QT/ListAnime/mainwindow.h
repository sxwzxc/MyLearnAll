#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QtQuickWidgets/QQuickWidget>
#include <QStandardItemModel>
#include "ListDelegate.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();
    QQuickWidget* qw;
    QStandardItemModel* pModel_;
    QStandardItem* pMsgItem;
    int aaa = 20;
    int index = 0;

protected:
    virtual void timerEvent(QTimerEvent* event);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow* ui;
};
#endif // MAINWINDOW_H
