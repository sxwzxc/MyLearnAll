// socketDNS.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//
#ifndef UNICODE
#define UNICODE
#endif

#define WIN32_LEAN_AND_MEAN
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS


#include <process.h>
#include <winsock2.h>
#include <Ws2tcpip.h>
#include <stdio.h>
//#include <stdlib.h>
#include <string>

// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

char dns_servers[1][16]; //���DNS��������IP
int dns_server_count = 0;

/*
**DNS�����в�ѯ����Ĳ�ѯ����
*/
#define A 1 //��ѯ���ͣ���ʾ���������IPv4��ַ 

void ngethostbyname(unsigned char*, int);
void ChangetoDnsNameFormat(unsigned char*, unsigned char*);

/*
**DNS�����ײ�
**����ʹ����λ��
*/
struct DNS_HEADER
{
    unsigned short id; //�Ự��ʶ
    unsigned char rd : 1; // ��ʾ�����ݹ�
    unsigned char tc : 1; // ��ʾ�ɽضϵ� 
    unsigned char aa : 1; //  ��ʾ��Ȩ�ش�
    unsigned char opcode : 4;
    unsigned char qr : 1; //  ��ѯ/��Ӧ��־��0Ϊ��ѯ��1Ϊ��Ӧ
    unsigned char rcode : 4; //Ӧ����
    unsigned char cd : 1;
    unsigned char ad : 1;
    unsigned char z : 1; //����ֵ
    unsigned char ra : 1; // ��ʾ���õݹ�
    unsigned short q_count; // ��ʾ��ѯ��������ڵ����� 
    unsigned short ans_count; // ��ʾ�ش����������
    unsigned short auth_count; // ��ʾ��Ȩ���������
    unsigned short add_count; // ��ʾ�������������
};

/*
**DNS�����в�ѯ��������
*/
struct QUESTION
{
    unsigned short qtype; //��ѯ����
    unsigned short qclass; //��ѯ��
};

typedef struct
{
    unsigned char* name;
    struct QUESTION* ques;
} QUERY;

/*
**DNS�����лش�����ĳ����ֶ�
*/
//�����Ƶ�����
#pragma pack(push, 1)//�������״̬���趨Ϊ1�ֽڶ���
struct R_DATA
{
    unsigned short type; //��ʾ��Դ��¼������
    unsigned short _class; //��
    unsigned int ttl; //��ʾ��Դ��¼���Ի����ʱ��
    unsigned short data_len; //���ݳ���
};
#pragma pack(pop) //�ָ�����״̬

/*
**DNS�����лش��������Դ�����ֶ�
*/
struct RES_RECORD
{
    unsigned char* name; //��Դ��¼����������
    struct R_DATA* resource; //��Դ����
    unsigned char* rdata;
};

int main(int argc, char* argv[])
{
    unsigned char hostname[100]= "www.baidu.com";
    unsigned char dns_servername[100];
    printf("������DNS��������IP��");
    //scanf("%s", dns_servername);
    std::string temp=(const char*) "4.2.2.1";
    strcpy(dns_servers[0], (const char*)temp.c_str());
    printf("������Ҫ��ѯIP����������");
    //scanf("%s", hostname);
    temp = "www.baidu.com";


    //���������IPv4��ַ��A�ǲ�ѯ����
    ngethostbyname(hostname, A);

    return 0;
}

/*
**ʵ��DNS��ѯ����
*/
void ngethostbyname(unsigned char* host, int query_type)
{
    unsigned char buf[65536], * qname, * reader;
    int i, j, stop;
    SOCKET s;

    struct sockaddr_in a; //��ַ

    struct RES_RECORD answers[20], auth[20], addit[20]; //�ش�������Ȩ���򡢸��������е���Դ�����ֶ�
    struct sockaddr_in dest; //��ַ

    struct DNS_HEADER* dns = NULL;
    struct QUESTION* qinfo = NULL;

    printf("\n�������������%s", host);

    s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP); //��������UDP�׽���

    dest.sin_family = AF_INET; //IPv4
    dest.sin_port = htons(53); //53�Ŷ˿�
    dest.sin_addr.s_addr = inet_addr(dns_servers[0]); //DNS������IP
    
    dns = (struct DNS_HEADER*)&buf;
    /*����DNS�����ײ�*/
    dns->id = (unsigned short)htons(_getpid()); //id��Ϊ���̱�ʶ��
    dns->qr = 0; //��ѯ
    dns->opcode = 0; //��׼��ѯ
    dns->aa = 0; //����Ȩ�ش�
    dns->tc = 0; //���ɽض�
    dns->rd = 1; //�����ݹ�
    dns->ra = 1; //���õݹ�
    dns->z = 0; //����Ϊ0
    dns->ad = 0;
    dns->cd = 0;
    dns->rcode = 0; //û�в��
    dns->q_count = htons(1); //1������
    dns->ans_count = 0;
    dns->auth_count = 0;
    dns->add_count = 0;

    //qnameָ���ѯ��������Ĳ�ѯ���ֶ�
    qname = (unsigned char*)&buf[sizeof(struct DNS_HEADER)];

    ChangetoDnsNameFormat(qname, host); //�޸�������ʽ 
    qinfo = (struct QUESTION*)&buf[sizeof(struct DNS_HEADER)
        + (strlen((const char*)qname) + 1)]; //qinfoָ�������ѯ����Ĳ�ѯ�����ֶ�

    qinfo->qtype = htons(query_type); //��ѯ����ΪA
    qinfo->qclass = htons(1); //��ѯ��Ϊ1

    //��DNS����������DNS������
    printf("\n\n���ͱ�����...");
    int iRet = sendto(s, (const char*)buf, sizeof(struct DNS_HEADER) + (strlen((const char*)qname) + 1) + sizeof(struct QUESTION), 0,
        (const sockaddr*)&dest, sizeof(dest));
    if (iRet < 0)
    {
        perror("����ʧ�ܣ�");
        printf("%d\n", iRet);
    }
    printf("���ͳɹ���");

    //��DNS����������DNS��Ӧ����
    i = sizeof dest;
    printf("\n���ձ�����...");
    if (recvfrom(s, (char*)buf, 65536, 0, (struct sockaddr*)&dest, (socklen_t*)&i) < 0)
    {
        perror("����ʧ�ܣ�");
    }
    printf("���ճɹ���");

    dns = (struct DNS_HEADER*)buf;

    //��readerָ����ձ��ĵĻش����� 
    reader = &buf[sizeof(struct DNS_HEADER) + (strlen((const char*)qname) + 1)
        + sizeof(struct QUESTION)];

    printf("\n\n��Ӧ���İ���: ");
    printf("\n %d������", ntohs(dns->q_count));
    printf("\n %d���ش�", ntohs(dns->ans_count));
    printf("\n %d����Ȩ����", ntohs(dns->auth_count));
    printf("\n %d�����Ӽ�¼\n\n", ntohs(dns->add_count));

    /*
    **�������ձ���
    */
    reader = reader + sizeof(short); //short���ͳ���Ϊ32Ϊ���൱�������ֶγ��ȣ���ʱreaderָ��ش�����Ĳ�ѯ�����ֶ�
    answers[i].resource = (struct R_DATA*)(reader);
    reader = reader + sizeof(struct R_DATA); //ָ��ش������������Դ�����ֶ�
    if (ntohs(answers[i].resource->type) == A) //�ж���Դ�����Ƿ�ΪIPv4��ַ
    {
        answers[i].rdata = (unsigned char*)malloc(ntohs(answers[i].resource->data_len)); //��Դ����
        for (j = 0; j < ntohs(answers[i].resource->data_len); j++)
        {
            answers[i].rdata[j] = reader[j];
        }
        answers[i].rdata[ntohs(answers[i].resource->data_len)] = '\0';
        reader = reader + ntohs(answers[i].resource->data_len);
    }

    //��ʾ��ѯ���
    if (ntohs(answers[i].resource->type) == A) //�жϲ�ѯ����IPv4��ַ
    {
        long* p;
        p = (long*)answers[i].rdata;
        a.sin_addr.s_addr = *p;
        printf("IPv4��ַ:%s\n", inet_ntoa(a.sin_addr));
    }

    return;
}

/*
**��www.baidu.comת����3www5baidu3com
*/
void ChangetoDnsNameFormat(unsigned char* dns, unsigned char* host)
{
    int lock = 0, i;
    strcat((char*)host, ".");

    for (i = 0; i < strlen((char*)host); i++)
    {
        if (host[i] == '.')
        {
            *dns++ = i - lock;
            for (; lock < i; lock++)
            {
                *dns++ = host[lock];
            }
            lock++;
        }
    }
    *dns++ = '\0';
}

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ����ʹ�ü���: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�
