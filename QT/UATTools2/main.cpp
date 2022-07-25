#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator *qtTranslator = new QTranslator;
    if (qtTranslator->load(":/language.qm")) {
        a.installTranslator(qtTranslator);
    }
    MainWindow w;
    w.show();
    return a.exec();
}
