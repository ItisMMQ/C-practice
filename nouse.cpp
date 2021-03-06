// Prog.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <WinSock2.h>
#include <time.h>
# include "winsock2.h"
# include "ws2tcpip.h"
# include<stdio.h>
#include <mstcpip.h>

using namespace std;

#define BUFFER_SIZE 65535
#pragma comment(lib,"ws2_32.lib")
#define IP_HDRINCL 1
typedef struct IP_Header
{
	unsigned char Version_HeaderLength;
	unsigned char TypeOfService;
	unsigned short TotalLength;
	unsigned short Identification;
	unsigned short Flags_FragmentOffset;
	unsigned char TimeToLive;
	unsigned char Protocal;
	unsigned short HeaderChecksum;
	unsigned long SourceAddress;
	unsigned long DestAddress;
}IPHEADER;

typedef struct Tcp_Header
{
	WORD SrcPort; // 源端口  
	WORD DstPort; // 目的端口
	DWORD SeqNum; // 顺序号
	DWORD AckNum; // 确认号
	BYTE DataOff; // TCP头长
	BYTE Flags; // 标志（URG、ACK等）
	WORD Window; // 窗口大小
	WORD Chksum; // 校验和
	WORD UrgPtr; // 紧急指针
}TCPHEADER;

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsData;
	WSAStartup(MAKEWORD(2, 2), &wsData);
	//int WSAStartup(WORD wVersionRequested,LPWSADATA lpWSAData);
	SOCKET sock;
	sock = WSASocket(AF_INET, SOCK_RAW, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);
	//int bind(SOCKET s,const struct sockaddr FAR *name,int nemelen);
	char localName[256];
	/*
	{
	cout<<"Create socket failed!"<<endl;
	return 3;
	}*/
	BOOL bFlag = TRUE;
	if (setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&bFlag, sizeof(bFlag)) == SOCKET_ERROR)
	{
		cout << "Setsockopt failed!" << endl;
		return 4;
	}
	gethostname(localName, 256);//获取本地主机名
	HOSTENT *pHost;
	pHost = gethostbyname(localName);
	sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(8000);
	addr_in.sin_addr = *(in_addr *)pHost->h_addr_list[0];
	bind(sock, (sockaddr *)&addr_in, sizeof(addr_in));
	struct hostent
	{
		char *h_name;
		char **h_aliases;
		int h_addrtype;
		int h_length;
		char **h_addr_list;
	};
#define IO_RCVALL _WSAIOW(IOC_VENDOR,1)
	DWORD dwBufferLen[10];
	DWORD dWBufferInLen = 1;
	DWORD dWByteReturned = 0;
	WSAIoctl(sock, IO_RCVALL, &dwBufferLen, sizeof(dWBufferInLen), &dwBufferLen, sizeof(dwBufferLen), &dWByteReturned, NULL, NULL);
	//int recv(SOCKET s,char FAR *buf,int len,int flags);
#define BUFFER_SIZE 65535
	char buffer[BUFFER_SIZE];//设置缓冲区
							 //CNodeList IpList;
	while (1)
	{
		int nPacketSize = recv(sock, buffer, BUFFER_SIZE, 0);
		if (nPacketSize>0)
		{
			IPHEADER *pIpHdr;
			pIpHdr = (IPHEADER *)buffer;
			if (pIpHdr->SourceAddress == addr_in.sin_addr.S_un.S_addr || pIpHdr->DestAddress == addr_in.sin_addr.S_un.S_addr)
			{
				//IpList.addNode(pIpHdr->SourceAddress,pIpHdr->DestAddress,pIpHdr->Protocal);
				switch (pIpHdr->Protocal)
				{
				case 1:cout << "the protocol is ICMP" << endl; break;
				case 2:cout << "the protocol is IGMP" << endl; break;
				case 4:cout << "the protocol is IP" << endl; break;
				case 6:cout << "the protocol is TCP" << endl; break;
				default:cout << "error!" << endl; break;

				}
			}
		}
	}
	return 0;
}

