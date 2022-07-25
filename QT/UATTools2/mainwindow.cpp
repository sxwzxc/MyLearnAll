#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QTextStream>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>
#include <QProcess>

const QString kHostPath = "C:/Windows/System32/drivers/etc/hosts";

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnAdd, &QPushButton::clicked, this, &MainWindow::slotBtnAdd);
    connect(ui->btnMod, &QPushButton::clicked, this, &MainWindow::slotBtnMod);
    connect(ui->btnDel, &QPushButton::clicked, this, &MainWindow::slotBtnDel);
    connect(ui->btnUAT, &QPushButton::clicked, this, &MainWindow::slotBtnUAT);
    connect(ui->btnWork, &QPushButton::clicked, this, &MainWindow::slotBtnWork);
    connect(ui->btnTest, &QPushButton::clicked, this, &MainWindow::slotBtnTest);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotBtnMod()
{
    file = new QFile(kHostPath);
    while (!file->open(QIODevice::ReadOnly));
    QTextStream textStream(file);
    QString fileText;
    fileText = textStream.readAll();
    qDebug() << fileText;
    int beginIndex = fileText.indexOf(tr("beginMark") + "\n");
    int endIndex = fileText.lastIndexOf(tr("endMark") + "\n");
    int length = endIndex - beginIndex + tr("endMark").size() + 1;
    fileText.remove(beginIndex, length);
    qDebug() << beginIndex;
    qDebug() << endIndex;
    file->close();
    file->open(QIODevice::WriteOnly);
    if (file->error() != QFileDevice::NoError)
    {
        QMessageBox::information(this, "Permission Denied!", tr("No Permission"));
    }
    textStream << fileText;
    file->close();
    QMessageBox::information(this, "Success", tr("Success"));
}

void MainWindow::slotBtnDel()
{
    system(R"("ncpa.cpl")");
}

void MainWindow::slotBtnUAT()
{
    QProcess cmd;
    cmd.start(tr("UATCmd")); //netsh interface ip set dnsservers name="以太网" static 52.83.74.116 primary
    cmd.waitForStarted();
    cmd.waitForFinished();
    cmd.start(tr("BothCmd")); //netsh interface ip add dns "以太网" 172.31.1.1 index=2
    cmd.waitForStarted();
    cmd.waitForFinished();
    system(R"(ipconfig /flushdns)");
    QMessageBox::information(this, "Success", tr("UAT Net Success Tip"));
}

void MainWindow::slotBtnWork()
{
    QProcess cmd;
    cmd.start(tr("WorkCmd")); //netsh interface ip set dnsservers name="以太网" static 10.20.193.2 primary
    cmd.waitForStarted();
    cmd.waitForFinished();
    cmd.start(tr("BothCmd")); //netsh interface ip add dns "以太网" 172.31.1.1 index=2
    cmd.waitForStarted();
    cmd.waitForFinished();
    system(R"(ipconfig /flushdns)");
    QMessageBox::information(this, "Success", tr("Work Net Success Tip"));
}

void MainWindow::slotBtnTest()
{
    system(R"("net stop AVP")");
    QProcess cmd;
    cmd.start(tr("UATCmd")); //netsh interface ip set dnsservers name="以太网" static 52.83.74.116 primary
    cmd.waitForStarted();
    cmd.waitForFinished();
    cmd.start(tr("BothCmd")); //netsh interface ip add dns "以太网" 172.31.1.1 index=2
    cmd.waitForStarted();
    cmd.waitForFinished();

    file = new QFile(kHostPath);
    file->open(QIODevice::ReadWrite | QIODevice::Append);
    if (file->error() != QFileDevice::NoError)
    {
        QMessageBox::information(this, "Permission Denied!", tr("No Permission"));
    }
    QTextStream txtOutput(file);
    txtOutput << endl;
    txtOutput << tr("beginMark") << endl;
    txtOutput << R"(172.29.150.130 tp-link.net)" << endl;
    txtOutput << R"(172.29.128.193 download.tp-link.net)" << endl;
    txtOutput << R"(172.29.89.66 bugzilla.tp-link.net)" << endl;
    txtOutput << R"(172.29.96.150 bugzilla.tp-link.com.cn)" << endl;
    txtOutput << R"(172.29.150.139 ams.tp-link.net)" << endl;
    txtOutput << R"(172.29.41.57 cert.tp-link.net)" << endl;
    txtOutput << R"(172.29.155.34 review.tp-link.net)" << endl;
    txtOutput << R"(172.29.150.133 erpapp.tp-link.net)" << endl;
    txtOutput << R"(172.29.89.22 tm.tp-link.net)" << endl;
    txtOutput << R"(172.29.150.141 dms.tp-link.net)" << endl;
    txtOutput << R"(172.29.182.32 oa.tp-link.net)" << endl;
    txtOutput << R"(172.31.1.200 rdsource.tp-link.net)" << endl;
    txtOutput << R"(172.29.182.48 login.tp-link.com.cn)" << endl;
    txtOutput << R"(172.29.89.61 testcase.tp-link.net)" << endl;
    txtOutput << R"(172.29.41.90 poprod.tp-link.net)" << endl;
    txtOutput << R"(172.29.41.86 selfservice.tp-link.net)" << endl;
    txtOutput << R"(172.29.152.230 testbed.tp-link.net)" << endl;
    txtOutput << R"(172.29.89.233 vpha.rd.tp-link.net)" << endl;
    txtOutput << R"(172.29.88.94 confluence.tp-link.net)" << endl;
    txtOutput << R"(172.29.89.57 rdtdcp.tp-link.net)" << endl;
    txtOutput << R"(172.29.41.128 oadoc.tp-link.net)" << endl;
    txtOutput << R"(172.29.102.193 vchat.rd.tp-link.net)" << endl;
    txtOutput << R"(172.29.88.68 rdscm.tp-link.net)" << endl;
    txtOutput << R"(172.29.160.31 mail.tp-link.com.cn)" << endl;
    txtOutput << tr("endMark") << endl;
    file->close();

    system(R"("shutdown -f -r -t 0")");

}

void MainWindow::slotBtnAdd()
{
    QMessageBox::warning(this, "Warning", tr("HostWarning"));
    QProcess cmd;
    cmd.start(tr("UATCmd")); //netsh interface ip set dnsservers name="以太网" static 52.83.74.116 primary
    cmd.waitForStarted();
    cmd.waitForFinished();
    cmd.start(tr("BothCmd")); //netsh interface ip add dns "以太网" 172.31.1.1 index=2
    cmd.waitForStarted();
    cmd.waitForFinished();
    system(R"(ipconfig /flushdns)");

    file = new QFile(kHostPath);
    file->open(QIODevice::ReadWrite | QIODevice::Append);
    if (file->error() != QFileDevice::NoError)
    {
        QMessageBox::information(this, "Permission Denied!", tr("No Permission"));
    }
    qDebug() << file->error();
    qDebug() << file->readAll();
    QTextStream txtOutput(file);
    txtOutput << endl;
    txtOutput << tr("beginMark") << endl;
    txtOutput << R"(172.29.150.130 tp-link.net)" << endl;
    txtOutput << R"(172.29.128.193 download.tp-link.net)" << endl;
    txtOutput << R"(172.29.89.66 bugzilla.tp-link.net)" << endl;
    txtOutput << R"(172.29.96.150 bugzilla.tp-link.com.cn)" << endl;
    txtOutput << R"(172.29.150.139 ams.tp-link.net)" << endl;
    txtOutput << R"(172.29.41.57 cert.tp-link.net)" << endl;
    txtOutput << R"(172.29.155.34 review.tp-link.net)" << endl;
    txtOutput << R"(172.29.150.133 erpapp.tp-link.net)" << endl;
    txtOutput << R"(172.29.89.22 tm.tp-link.net)" << endl;
    txtOutput << R"(172.29.150.141 dms.tp-link.net)" << endl;
    txtOutput << R"(172.29.182.32 oa.tp-link.net)" << endl;
    txtOutput << R"(172.31.1.200 rdsource.tp-link.net)" << endl;
    txtOutput << R"(172.29.182.48 login.tp-link.com.cn)" << endl;
    txtOutput << R"(172.29.89.61 testcase.tp-link.net)" << endl;
    txtOutput << R"(172.29.41.90 poprod.tp-link.net)" << endl;
    txtOutput << R"(172.29.41.86 selfservice.tp-link.net)" << endl;
    txtOutput << R"(172.29.152.230 testbed.tp-link.net)" << endl;
    txtOutput << R"(172.29.89.233 vpha.rd.tp-link.net)" << endl;
    txtOutput << R"(172.29.88.94 confluence.tp-link.net)" << endl;
    txtOutput << R"(172.29.89.57 rdtdcp.tp-link.net)" << endl;
    txtOutput << R"(172.29.41.128 oadoc.tp-link.net)" << endl;
    txtOutput << R"(172.29.102.193 vchat.rd.tp-link.net)" << endl;
    txtOutput << R"(172.29.88.68 rdscm.tp-link.net)" << endl;
    txtOutput << R"(172.29.160.31 mail.tp-link.com.cn)" << endl;
    txtOutput << tr("endMark") << endl;
    file->close();

    QMessageBox::information(this, "Success", tr("Enjoy!"));
}

