#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_NativeWindows);
    //a.setAttribute(Qt::AA_NativeWindows, false);
    a.setAttribute(Qt::AA_DontCreateNativeWidgetSiblings);
    MainWindow w;
    w.setAttribute(Qt::WA_DontCreateNativeAncestors);
    w.show();
    return a.exec();
}
