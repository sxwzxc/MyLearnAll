/*
 *ģ��DNSЭ��Ĺ���
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
  *ģ��DNSЭ��Ĺ���
  */


#pragma comment(lib , "ws2_32.lib")
#pragma comment(lib , "IPHLPAPI.LIB")
#pragma pack(2) //�����ֽڶ�������
#define PORT 53 //����˿ں�
#define TIMEOUT 3000 //��ʱʱ��

typedef struct //DNS�����ײ�
{
    unsigned short id;
    unsigned short flags;
    unsigned short questNum;
    unsigned short answerNum;
    unsigned short authorNum;
    unsigned short additionNum;
} DNSHDR, * pDNSHDR;

typedef struct //DNS���Ĳ�ѯ��¼
{
    unsigned short type;
    unsigned short queryclass;
} QUERYHDR, * pQUERYHDR;

typedef struct //DNS����Ӧ���¼
{
    unsigned short type;
    unsigned short classes;
    unsigned long ttl;
    unsigned short length;
} RESPONSE, * pRESPONSE;

/*
 *����һ��DNS������
 */
int genDNSPacket(pDNSHDR pDnsHdr, pQUERYHDR pQueryHdr, char* hostname, char* DNSsendBuff);

/*
 *�Խ��յ���DNSӦ���Ľ��н����õ���Ҫ��IP��ַ��Ϣ
 */
void decodeDNSPacket(char* DNSrecvBuff);

/*
 *��ȡ�������õ�DNS������
 */
void getDnsServer(char* dnsServer);

/*
 *����������
 */
int main()
{
    sockaddr_in addr; //�󶨵�ַ
    SOCKET ListenSocket; //����������õ�SOCKET
    int len = 0;

    //��ʼ��WinSock
    WORD wVersionRequested = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(wVersionRequested, &wsaData) != 0)
    {
        printf("��ʼ��WinSockʧ�ܣ�\n");
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
    addr.sin_addr.s_addr = htonl(INADDR_ANY); //�κε�ַ
    addr.sin_port = htons(PORT);
    //���м����˿ڵİ�
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


    //����UDP���ݱ��ķ���
    int sent;
    hostent* hostdata;
    if (atoi(dnsip)) //�Ƿ�ΪIP��ַ�ı�׼��ʽ
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
    sockaddr_in dest; //��дĿ�ĵ�ַ��Ϣ
    dest.sin_family = PF_INET;
    //��hostent�ṹ�������h_addr_listת��Ϊin_addr���͵ĵ�ַ��Ϣ

    dest.sin_addr.s_addr = inet_addr(dnsip); //DNS������IP

    //dest.sin_addr = *(in_addr*)(hostdata->h_addr_list[0]);
    dest.sin_port = htons(PORT);

    //��ȡDNS����
    char hostname[30], buffer[100];
    DNSHDR dnsHdr;
    QUERYHDR queryHdr;
    //printf("Please input domain name (no more than 30) : ");
    printf("��Ҫ��ѯ������: ");
    scanf("%s", hostname);
    printf("��ָ��DNS������������Ĭ��Ϊ4.2.2.1 : ");
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

    //�������ݵĽ���
    char buf[400];
    sockaddr_in dnsServer;
    int addr_len = sizeof(dnsServer);
    int result;
    while (1) //���յ�����ʱ�˳�
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
 *����һ��DNS������
 *���ɵ�DNS�����ı�����DNSsendBuff��
 *hostnameΪ��Ҫ��ѯ�������ַ���
 *����ֵΪ���������ĵĳ��ȣ���λΪ�ֽ�
 */
int genDNSPacket(pDNSHDR pDnsHdr, pQUERYHDR pQueryHdr, char* hostname, char* DNSsendBuff)
{
    if (!strcmp(hostname, "exit"))
    {
        return -1; //����exitʱ����
    }
    else //������DNS��ѯ����
    {
        int iSendByte = 0;
        ZeroMemory(DNSsendBuff, sizeof(DNSsendBuff));
        pDnsHdr->id = htons(0x0000); //"��ʶ"�ֶ�����Ϊ0
        pDnsHdr->flags = htons(0x0100); //"��־"�ֶ�����Ϊ0x0100, ��RDλΪ1�����ݹ��ѯ
        pDnsHdr->questNum = htons(0x0001); //1����ѯ��¼
        pDnsHdr->answerNum = htons(0x0000); //û�лش��¼�������ļ�¼
        pDnsHdr->authorNum = htons(0x0000);
        pDnsHdr->additionNum = htons(0x0000);
        //�����ɵ�DNS��ѯ�����ײ����Ƶ�DNSsendBuff��
        memcpy(DNSsendBuff, pDnsHdr, sizeof(DNSHDR));
        iSendByte += sizeof(DNSHDR); //��¼��ǰ��������

        //�������ַ������н������ҽ�����ʽ�ı任
        char* pTrace = hostname;
        char* pHostname = hostname;
        int iStrLen = strlen(hostname);
        unsigned char iCharNum = 0;
        //��ָ��ָ����ַ�������ƶ�һ���ֽ�
        while (*pTrace != '\0')
        {
            pTrace++;
        }
        while (pTrace != hostname)
        {
            *(pTrace + 1) = *pTrace;
            pTrace--;
        }

        *(pTrace + 1) = *pTrace; //����һ���ַ��ƶ����ڶ����ַ���λ��

        pTrace++; //��һ���ַ���ʵ�����壬�ƶ����ڶ����ַ�λ��
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

        //�����һ���ַ�'.'֮����ַ���д��
        *pHostname = iCharNum;
        memcpy(DNSsendBuff + sizeof(DNSHDR), hostname, iStrLen + 2);
        iSendByte += (iStrLen + 2); //������֮����������ַ�

        //�������ֶ�֮�����롰��ѯ���͡��͡���ѯ�ࡱ
        pQueryHdr->type = htons(0x0001);
        pQueryHdr->queryclass = htons(0x0001);
        memcpy(DNSsendBuff + sizeof(DNSHDR) + (iStrLen + 2), pQueryHdr, sizeof(QUERYHDR));

        iSendByte += sizeof(QUERYHDR); // �ۼӵõ����ֽ���
        return iSendByte; //�������յõ����ֽ���
    }
}

/*
 *�����յ���DNS����DNSrecvBuff
 *Ӧ���¼�ֶ�������Ϊ5ʱ��Ϊ������һ�������������˶�Ӧ���¼������Ϊ1ʱ����ʾ����
 */
void decodeDNSPacket(char* DNSrecvBuff)
{
    pDNSHDR pDnsHdr = (pDNSHDR)DNSrecvBuff; //ָ��pDnsHdrָ����յ���DNSӦ�����ײ�

    //�������и�����Ϣ
    int iQueryNum, iRespNum, iAuthRespNum, iAdditionNum;
    iQueryNum = ntohs(pDnsHdr->questNum);
    iRespNum = ntohs(pDnsHdr->answerNum);
    iAuthRespNum = ntohs(pDnsHdr->authorNum);
    iAdditionNum = ntohs(pDnsHdr->additionNum);

    //��DNSӦ���ĵġ���־���ֶ�����15λ��ȡ���λ �� 0 ΪDNS��ѯ���ģ�1ΪӦ����
    if (pDnsHdr->flags >> 15)
    {
        //flags��λֵΪ3����ʶ������û��������������Ӧ�ļ�¼
        if ((pDnsHdr->flags & 0x0007) == 3)
        {
            printf("No corresponding domain name entry . \n");
            return;
        }
        if ((pDnsHdr->flags >> 10) & 0x0001) //�鿴��־λAA�����Ƿ�ʱȨ��Ӧ��
        {
            printf("Authoritative anwser : \n");
        }
        else
        {
            printf("None-authoritative anwser : \n");
        }

        char* pTraceResponse;
        //ָ������Ӧ�����еĵ�һ����ѯ��¼����Ϊһ�������Ӧ���ľ������ȸ���һ����Ӧ�Ĳ�ѯ��¼
        pTraceResponse = DNSrecvBuff + sizeof(DNSHDR);

        //��ָ���ƶ�����ѯ��¼�������ֶ�֮��
        while (*pTraceResponse)
        {
            pTraceResponse++;
        }
        pTraceResponse++;

        //������ѯ���ͺͲ�ѯ�������ֶΣ�ָ��ָ���һ��Ӧ���¼
        pTraceResponse += sizeof(long);
        in_addr address;
        pRESPONSE pResponse;
        printf("Addresses : ");
        for (int i = 0; i < iRespNum; i++)
        {
            //ָ������Ӧ���¼�ġ��������ֶΣ��������ֶ�һ��Ϊһ������ָ�룬��0xC0��ʼ
            pTraceResponse += sizeof(short);
            pResponse = (pRESPONSE)pTraceResponse;
            if (ntohs(pResponse->type) == 1) //����Ӧ���¼���ص�����֮ǰ��ѯ����Ӧ��IP��ַ
            {
                pTraceResponse += sizeof(RESPONSE);
                unsigned long ulIP = *(unsigned long*)pTraceResponse;
                address.s_addr = ulIP;
                if (i == iRespNum - 1) //���һ����¼��ʾ��ţ�������ʾ�ֺ�
                {
                    printf("%s . ", inet_ntoa(address));
                }
                else
                {
                    printf("%s ; ", inet_ntoa(address));
                }

                //ָ���ƹ�Ӧ���¼��IP��ַ�ֶΣ�ָ����һ��Ӧ���¼
                pTraceResponse += sizeof(long);
            }
            else if (ntohs(pResponse->type) == 5) //����Ӧ���¼Ϊ����ѯ������һ�����������ﱾ����ֱ������������¼
            {
                pTraceResponse += sizeof(RESPONSE);
                pTraceResponse += ntohs(pResponse->length);
            }
        }
        printf("\n");
    }
    else //��־�ֶ����λ��Ϊ1����ʾ����һ��DNSӦ���ģ������κδ���
    {
        printf("Invalid DNS resolution ! \n\n");
    }
}

/*
 *��ñ������õ�DNS��������Ϣ�����浽dnsServer����
 */
void getDnsServer(char* dnsServer)
{
    //�����Ҫ�Ļ�������С
    DWORD nLength = 0;
    if (GetNetworkParams(NULL, &nLength) != ERROR_BUFFER_OVERFLOW)
    {
        return;
    }
    FIXED_INFO* pFixedInfo = (FIXED_INFO*)new BYTE[nLength];

    //��ñ��ص��������
    if (GetNetworkParams(pFixedInfo, &nLength) != ERROR_SUCCESS)
    {
        delete[] pFixedInfo;
        return;
    }
    IP_ADDR_STRING* pCurrentDnsServer = &pFixedInfo->DnsServerList;
    if (pCurrentDnsServer != NULL)
    {
        //pCurrentDnsServer->IpAddress.String ��Ϊ����Ҫ�ַ�����ʽ��DNS������
        char* tmp = pCurrentDnsServer->IpAddress.String;
        strcpy(dnsServer, tmp);
    }
}