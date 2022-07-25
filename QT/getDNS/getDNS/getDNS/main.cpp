#include "getDNS.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    getDNS w;
    w.show();
    return a.exec();
}
