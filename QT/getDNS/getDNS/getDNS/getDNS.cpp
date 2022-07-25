#define WIN32_LEAN_AND_MEAN

#include "getDNS.h"
#include <QDnsLookup>
#include <QDebug>
#include <QHostAddress>
#include <QPushButton>
#include <windows.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
//����DNS����       ID       tag       numq      numa       numa1    numa2
char DNS_DATA[] = { 0x12,0x34,0x01,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,
0x03,0x77,0x77,0x77,0x06,0x66,0x75,0x68,0x6f,0x6d,0x65,0x03,0x6e,0x65,0x74,0x00,//03 www 06 fucome 03 net 00
0x00,0x01,0x00,0x01 };//ǰ���ֽ�Ϊ1��ʾA��¼; �����ֽ�Ϊ1��ʾDNS_HDR+����+DNS_QER

getDNS::getDNS(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    qDebug() << "start";
    lookup.setNameserver(QHostAddress("8.8.8.8"));
    qDebug() << lookup.nameserver();
    lookup.setName("tp-link.net");
    connect(&lookup, &QDnsLookup::finished, [=]() {
        auto records = lookup.hostAddressRecords();
        for (auto record : records)
        {
            qDebug() << record.timeToLive() << "; " <<
                record.value().toString() << '\n';
        }
        auto records2 = lookup.nameServerRecords();
        for (auto record : records2)
        {
            qDebug() << record.timeToLive() << "; " <<
                record.value() << '\n';
        }
    });
   // lookup.lookup();
    //auto records = lookup.hostAddressRecords();
    //for (auto record : records)
    //{
    //    qDebug() << record.timeToLive() << "; " <<
    //        record.value().toString() << '\n';
    //}

    connect(ui.btn, &QPushButton::clicked, [=]() {
        //lookup.setNameserver(QHostAddress("8.8.8.8"));
        //lookup.lookup();
        socketDNS();
    });
    
    QDnsLookup* lookup2 = new QDnsLookup(QDnsLookup::ANY, "office.com", QHostAddress(IPV4StringToInteger("4.2.2.1")));
    connect(lookup2, &QDnsLookup::finished, [=]() {
        qDebug() << lookup2->nameserver();
        auto records = lookup2->hostAddressRecords();
        for (auto record : records)
        {
            qDebug() << record.name() << "->" <<
                record.value().toString() << '\n';
        }
    });
    lookup2->lookup();



}

quint32 getDNS::IPV4StringToInteger(const QString& ip) {
    QStringList ips = ip.split(".");
    if (ips.size() == 4) {
        return ips.at(3).toInt()
            | ips.at(2).toInt() << 8
            | ips.at(1).toInt() << 16
            | ips.at(0).toInt() << 24;
    }
    return 0;
}

int getDNS::socketDNS()
{
    WORD socketVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(socketVersion, &wsaData) != 0)
    {
        printf("error");
        return 0;
    }
    //����UDPͨ���׽���
    SOCKET sclient = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); 

    SOCKADDR_IN sin;
    sin.sin_family = AF_INET;
    sin.sin_port = htons(53);//DNSԶ�̶˿ڹ̶�Ϊ53
    sin.sin_addr.S_un.S_addr = inet_addr("114.114.114.114");//DNS������IP��ַ�����������ص�ַ��(192.168.0.1)

    //������������
    sendto(sclient, DNS_DATA, sizeof(DNS_DATA), 0, (SOCKADDR*)&sin, sizeof(sin));

    char recvData[255];
    int ret = recv(sclient, recvData, 255, 0);//�ȴ���������
    if (ret > 0)//�յ�����0������
    {
        for (int i = 0; i < ret; i++)//��16���Ƹ�ʽ��ӡ����
        {
            printf("%02X ", (unsigned char)recvData[i]);
        }
    }

    closesocket(sclient);
    WSACleanup();
    return 0;
}
