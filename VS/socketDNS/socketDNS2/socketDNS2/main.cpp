/*
 *模拟DNS协议的工作
 */
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>
#include<Winsock2.h>
#include<Iphlpapi.h>
#include<windows.h>
#include<string.h>
#pragma comment(lib , "ws2_32.lib")
#pragma comment(lib , "IPHLPAPI.LIB")
 /*
  *模拟DNS协议的工作
  */


#pragma comment(lib , "ws2_32.lib")
#pragma comment(lib , "IPHLPAPI.LIB")
#pragma pack(2) //设置字节对齐属性
#define PORT 53 //定义端口号
#define TIMEOUT 3000 //超时时间

typedef struct //DNS报文首部
{
    unsigned short id;
    unsigned short flags;
    unsigned short questNum;
    unsigned short answerNum;
    unsigned short authorNum;
    unsigned short additionNum;
} DNSHDR, * pDNSHDR;

typedef struct //DNS报文查询记录
{
    unsigned short type;
    unsigned short queryclass;
} QUERYHDR, * pQUERYHDR;

typedef struct //DNS报文应答记录
{
    unsigned short type;
    unsigned short classes;
    unsigned long ttl;
    unsigned short length;
} RESPONSE, * pRESPONSE;

/*
 *生成一个DNS请求报文
 */
int genDNSPacket(pDNSHDR pDnsHdr, pQUERYHDR pQueryHdr, char* hostname, char* DNSsendBuff);

/*
 *对接收到的DNS应答报文进行解析得到需要的IP地址信息
 */
void decodeDNSPacket(char* DNSrecvBuff);

/*
 *获取本机配置的DNS服务器
 */
void getDnsServer(char* dnsServer);

/*
 *测试主函数
 */
int main()
{
    sockaddr_in addr; //绑定地址
    SOCKET ListenSocket; //发送与接收用的SOCKET
    int len = 0;

    //初始化WinSock
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(wVersionRequested, &wsaData) != 0)
    {
        printf("初始化WinSock失败！\n");
        return 0;
    }

    ListenSocket = socket(PF_INET, SOCK_DGRAM, 0);
    if (ListenSocket == INVALID_SOCKET)
    {
        printf("Error : socket create failed ! \n");
        fflush(0);
        return 0;
    }
    addr.sin_family = PF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //任何地址
    addr.sin_port = htons(PORT);
    //进行监听端口的绑定
    if (bind(ListenSocket, (struct sockaddr*)&addr, sizeof(addr)) != 0)
    {
        printf("Error : bind failed !\n");
        fflush(0);
        closesocket(ListenSocket);
        return 0;
    }
    char dnsip[20];
    getDnsServer(dnsip);
    //strcpy(dnsip, (const char*)"10.20.193.2");
    strcpy(dnsip, (const char*)"4.2.2.1");


    //进行UDP数据报的发送
    int sent;
    hostent* hostdata;
    if (atoi(dnsip)) //是否为IP地址的标准形式
    {
        u_long ip = inet_addr(dnsip);
        hostdata = gethostbyaddr((char*)&ip, sizeof(ip), PF_INET);
    }
    else
    {
        printf("The DNS IP is not correct ! \n");
        return 0;
    }
    if (!hostdata)
    {
        printf("Get the name error ! \n");
        fflush(0);
        return 0;
    }
    sockaddr_in dest; //填写目的地址信息
    dest.sin_family = PF_INET;
    //将hostent结构体里面的h_addr_list转化为in_addr类型的地址信息

    dest.sin_addr.s_addr = inet_addr(dnsip); //DNS服务器IP

    //dest.sin_addr = *(in_addr*)(hostdata->h_addr_list[0]);
    dest.sin_port = htons(PORT);

    //获取DNS报文
    char hostname[30], buffer[100];
    DNSHDR dnsHdr;
    QUERYHDR queryHdr;
    //printf("Please input domain name (no more than 30) : ");
    printf("需要查询的域名: ");
    scanf("%s", hostname);
    printf("请指定DNS服务器，留空默认为4.2.2.1 : ");
    char hostname2[30];
    scanf("%s",hostname2);
    len = genDNSPacket(&dnsHdr, &queryHdr, hostname, buffer);
    sent = sendto(ListenSocket, buffer, len, 0, (sockaddr*)&dest, sizeof(sockaddr_in));
    if (sent != len)
    {
        printf("Error : send error !\n");
        fflush(0);
        return 0;
    }

    //进行数据的接收
    char buf[400];
    sockaddr_in dnsServer;
    int addr_len = sizeof(dnsServer);
    int result;
    while (1) //接收到数据时退出
    {
        result = recvfrom(ListenSocket, buf, sizeof(buf) - 1, 0, (sockaddr*)&dnsServer, &addr_len);
        if (result > 0)
        {
            buf[result] = 0;
            decodeDNSPacket(buf);
            break;
        }
    }

    return 0;
}

/*
 *生成一个DNS请求报文
 *生成的DNS请求报文保存在DNSsendBuff中
 *hostname为需要查询的域名字符串
 *返回值为生成请求报文的长度，单位为字节
 */
int genDNSPacket(pDNSHDR pDnsHdr, pQUERYHDR pQueryHdr, char* hostname, char* DNSsendBuff)
{
    if (!strcmp(hostname, "exit"))
    {
        return -1; //输入exit时结束
    }
    else //正常的DNS查询请求
    {
        int iSendByte = 0;
        ZeroMemory(DNSsendBuff, sizeof(DNSsendBuff));
        pDnsHdr->id = htons(0x0000); //"标识"字段设置为0
        pDnsHdr->flags = htons(0x0100); //"标志"字段设置为0x0100, 即RD位为1期望递归查询
        pDnsHdr->questNum = htons(0x0001); //1个查询记录
        pDnsHdr->answerNum = htons(0x0000); //没有回答记录和其它的记录
        pDnsHdr->authorNum = htons(0x0000);
        pDnsHdr->additionNum = htons(0x0000);
        //将生成的DNS查询报文首部复制到DNSsendBuff中
        memcpy(DNSsendBuff, pDnsHdr, sizeof(DNSHDR));
        iSendByte += sizeof(DNSHDR); //记录当前的数据量

        //对域名字符串进行解析并且进行形式的变换
        char* pTrace = hostname;
        char* pHostname = hostname;
        int iStrLen = strlen(hostname);
        unsigned char iCharNum = 0;
        //将指针指向的字符串向后移动一个字节
        while (*pTrace != '\0')
        {
            pTrace++;
        }
        while (pTrace != hostname)
        {
            *(pTrace + 1) = *pTrace;
            pTrace--;
        }

        *(pTrace + 1) = *pTrace; //将第一个字符移动到第二个字符的位置

        pTrace++; //第一个字符无实际意义，移动到第二个字符位置
        while (*pTrace != '\0')
        {
            if (*pTrace == '.')
            {
                *pHostname = iCharNum;
                iCharNum = 0;
                pHostname = pTrace;
            }
            else
            {
                iCharNum++;
            }
            pTrace++;
        }

        //将最后一个字符'.'之后的字符树写入
        *pHostname = iCharNum;
        memcpy(DNSsendBuff + sizeof(DNSHDR), hostname, iStrLen + 2);
        iSendByte += (iStrLen + 2); //解析完之后会多出两个字符

        //在域名字段之后填入“查询类型”和“查询类”
        pQueryHdr->type = htons(0x0001);
        pQueryHdr->queryclass = htons(0x0001);
        memcpy(DNSsendBuff + sizeof(DNSHDR) + (iStrLen + 2), pQueryHdr, sizeof(QUERYHDR));

        iSendByte += sizeof(QUERYHDR); // 累加得到的字节数
        return iSendByte; //返回最终得到的字节数
    }
}

/*
 *解析收到的DNS报文DNSrecvBuff
 *应答记录字段中类型为5时即为域名的一个别名，跳过此段应答记录，类型为1时即显示出来
 */
void decodeDNSPacket(char* DNSrecvBuff)
{
    pDNSHDR pDnsHdr = (pDNSHDR)DNSrecvBuff; //指针pDnsHdr指向接收到的DNS应答报文首部

    //保存所有附加信息
    int iQueryNum, iRespNum, iAuthRespNum, iAdditionNum;
    iQueryNum = ntohs(pDnsHdr->questNum);
    iRespNum = ntohs(pDnsHdr->answerNum);
    iAuthRespNum = ntohs(pDnsHdr->authorNum);
    iAdditionNum = ntohs(pDnsHdr->additionNum);

    //将DNS应答报文的“标志”字段右移15位即取最高位 ， 0 为DNS查询报文，1为应答报文
    if (pDnsHdr->flags >> 15)
    {
        //flags低位值为3，标识服务器没有与请求域名相应的记录
        if ((pDnsHdr->flags & 0x0007) == 3)
        {
            printf("No corresponding domain name entry . \n");
            return;
        }
        if ((pDnsHdr->flags >> 10) & 0x0001) //查看标志位AA，看是否时权威应答
        {
            printf("Authoritative anwser : \n");
        }
        else
        {
            printf("None-authoritative anwser : \n");
        }

        char* pTraceResponse;
        //指针移向应答报文中的第一个查询记录，因为一般情况下应答报文均会首先附带一个对应的查询记录
        pTraceResponse = DNSrecvBuff + sizeof(DNSHDR);

        //将指针移动到查询记录的域名字段之后
        while (*pTraceResponse)
        {
            pTraceResponse++;
        }
        pTraceResponse++;

        //跳过查询类型和查询类两个字段，指针指向第一个应答记录
        pTraceResponse += sizeof(long);
        in_addr address;
        pRESPONSE pResponse;
        printf("Addresses : ");
        for (int i = 0; i < iRespNum; i++)
        {
            //指针跳过应答记录的“域名”字段，此域名字段一般为一个域名指针，以0xC0开始
            pTraceResponse += sizeof(short);
            pResponse = (pRESPONSE)pTraceResponse;
            if (ntohs(pResponse->type) == 1) //这条应答记录返回的是与之前查询所对应的IP地址
            {
                pTraceResponse += sizeof(RESPONSE);
                unsigned long ulIP = *(unsigned long*)pTraceResponse;
                address.s_addr = ulIP;
                if (i == iRespNum - 1) //最后一条记录显示句号，否则显示分号
                {
                    printf("%s . ", inet_ntoa(address));
                }
                else
                {
                    printf("%s ; ", inet_ntoa(address));
                }

                //指针移过应答记录的IP地址字段，指向下一条应答记录
                pTraceResponse += sizeof(long);
            }
            else if (ntohs(pResponse->type) == 5) //这条应答记录为所查询主机的一个别名，这里本程序直接跳过这条记录
            {
                pTraceResponse += sizeof(RESPONSE);
                pTraceResponse += ntohs(pResponse->length);
            }
        }
        printf("\n");
    }
    else //标志字段最高位不为1，表示不是一个DNS应答报文，不做任何处理
    {
        printf("Invalid DNS resolution ! \n\n");
    }
}

/*
 *获得本机设置的DNS服务器信息并保存到dnsServer里面
 */
void getDnsServer(char* dnsServer)
{
    //获得需要的缓冲区大小
    DWORD nLength = 0;
    if (GetNetworkParams(NULL, &nLength) != ERROR_BUFFER_OVERFLOW)
    {
        return;
    }
    FIXED_INFO* pFixedInfo = (FIXED_INFO*)new BYTE[nLength];

    //获得本地的网络参数
    if (GetNetworkParams(pFixedInfo, &nLength) != ERROR_SUCCESS)
    {
        delete[] pFixedInfo;
        return;
    }
    IP_ADDR_STRING* pCurrentDnsServer = &pFixedInfo->DnsServerList;
    if (pCurrentDnsServer != NULL)
    {
        //pCurrentDnsServer->IpAddress.String 即为所需要字符串形式的DNS服务器
        char* tmp = pCurrentDnsServer->IpAddress.String;
        strcpy(dnsServer, tmp);
    }
}