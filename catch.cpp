
// Demo05.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <WinSock2.h>
#include <iostream>
#include <time.h>
#include <string.h>

using namespace std;

#pragma comment(lib,"ws2_32.lib")
#define IO_RCVALL _WSAIOW(IOC_VENDOR,1)
#define BUFFER_SIZE   65535
#define IP_HDRINCL 1

typedef struct Ip_Header
{
	unsigned char      Version_HeaderLength;
	unsigned char      TypeOfService;
	unsigned short     TotalLength;
	unsigned short     Identification;
	unsigned short     Flages_FragmentOffset;
	unsigned char      TimeToLive;
	unsigned char      Protocal;
	unsigned short     HeaderChecksum;
	unsigned long      SourceAddress;
	unsigned long      DestAddress;
}IPHEADER;

struct TCPHead
{
	USHORT usSourcePort;
	USHORT usDestPort;
	ULONG  dwSeq;
	ULONG  dwAck;
	UCHAR  ucLength;
	UCHAR  ucFlag;
	USHORT usWindow;
	USHORT usCheckSum;
	USHORT usUrgent;
	UINT   unMssOpt;
	USHORT unNopOpt;
	USHORT usSackOpt;

};
struct HTTP
{
	unsigned char a[20];
};

struct UDPHead
{
	u_short usSourcePort;
	u_short usDestPort;
	u_short usLength;
	u_short usCheckSum;
};


int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsData;
	WSAStartup(MAKEWORD(2, 2), &wsData);

	SOCKET socket;
	socket = WSASocket(AF_INET, SOCK_RAW, IPPROTO_IP, NULL, 0, WSA_FLAG_OVERLAPPED);

	BOOL bFlag = TRUE;

	if (setsockopt(socket, IPPROTO_IP, IP_HDRINCL, (char *)&bFlag, sizeof(bFlag)) == SOCKET_ERROR)
	{
		printf("Setsockopt failed!");
		system("pause");
		return 4;
	}

	char localName[256];
	gethostname(localName, 256);
	HOSTENT *pHost;
	pHost = gethostbyname(localName);
	sockaddr_in addr_in;
	addr_in.sin_family = AF_INET;
	addr_in.sin_port = htons(8000);
	addr_in.sin_addr = *(in_addr *)pHost->h_addr_list[0];

	bind(socket, (sockaddr *)&addr_in, sizeof(addr_in));

	DWORD dwBufferLen[10];
	DWORD dwBufferInLen = 1;
	DWORD dwBytesReturned = 0;
	WSAIoctl(socket, IO_RCVALL, &dwBufferInLen, sizeof(dwBufferInLen), &dwBufferLen, sizeof(dwBufferLen), &dwBytesReturned, NULL, NULL);

	char buffer[BUFFER_SIZE];
	//CNodeList IpList;

	while (1)           //此处应填入设置的捕获时间
	{
		int nPacketSize = recv(socket, buffer, BUFFER_SIZE, 0);

		if (nPacketSize > 0)
		{
			TCPHead *pTcp;
			UDPHead *pUdp;
			IPHEADER *pIpHdr;
			HTTP *http;
			pIpHdr = (IPHEADER *)buffer;
			// pTcp = (TcpHead *)(pIpHdr.Hdrlen&IP_HDRLEN_MASK);
			pTcp = (TCPHead *)(buffer + sizeof(IPHEADER));
			pUdp = (UDPHead *)(buffer + sizeof(IPHEADER));


			//(pIpHdr->SourceAddress == addr_in.sin_addr.S_un.S_addr||pIpHdr->DestAddress == addr_in.sin_addr.S_un.S_addr)  inet_ntoa(addr_in.sin_addr.S_un.S_addr)
			if ((htons(pTcp->usDestPort) == 80) && (pIpHdr->SourceAddress == addr_in.sin_addr.S_un.S_addr || pIpHdr->DestAddress == addr_in.sin_addr.S_un.S_addr))
			{
				//http = (HTTP *)(buffer+40);
				in_addr address1, address2;
				address1.S_un.S_addr = pIpHdr->SourceAddress;
				address2.S_un.S_addr = pIpHdr->DestAddress;
				switch (pIpHdr->Protocal)
				{
				case 1: printf("the protocol is ICMP\n"); break;
				case 2:printf("the protocol is IGMP\n"); break;
				case 6:printf("the protocol is TCP \n");
					cout << "Source port of TCP： " << htons(pTcp->usSourcePort) << endl;
					cout << "Dest port of TCP：" << htons(pTcp->usDestPort) << endl;
					break;
				case 8:cout << "The protocol is EGP\n" << endl; break;
				case 17:cout << "The protocol is UDP\n" << endl;
					cout << "Source port of UDP:  " << htons(pUdp->usSourcePort) << endl;
					cout << "Dest port of UDP：" << htons(pUdp->usDestPort) << endl;
					cout << "Length of UDP：" << htons(pUdp->usLength) << endl;
					break;
				}
				cout << "This data is form cqupt: " << inet_ntoa(address1) << inet_ntoa(address2) << pIpHdr->Protocal << endl;

			}
		}
	}

	return 0;
}


