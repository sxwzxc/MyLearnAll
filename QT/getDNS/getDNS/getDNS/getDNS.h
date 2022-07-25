#pragma once

#include <QDnsLookup>
#include <QtWidgets/QMainWindow>
#include "ui_getDNS.h"

class getDNS : public QMainWindow
{
    Q_OBJECT

public:
    getDNS(QWidget *parent = Q_NULLPTR);
    quint32 IPV4StringToInteger(const QString& ip);
    int socketDNS();

private:
    Ui::getDNSClass ui;
    QDnsLookup lookup;
};
