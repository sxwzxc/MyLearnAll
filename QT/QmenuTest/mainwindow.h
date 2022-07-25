#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QEvent>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void on_pushButton_clicked();

private:
	Ui::MainWindow *ui;
};

#include <QMenu>
class MyMenu : public QMenu
{
	Q_OBJECT

public:
	MyMenu(QWidget *parent);
	~MyMenu();
protected:
	void leaveEvent(QEvent * e);
};






#endif // MAINWINDOW_H
