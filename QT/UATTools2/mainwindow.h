#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow* ui;
    QFile* file;

private slots:
    void slotBtnAdd();
    void slotBtnMod();
    void slotBtnDel();
    void slotBtnUAT();
    void slotBtnWork();
    void slotBtnTest();
};
#endif // MAINWINDOW_H
