// WebServer.c: 定义控制台应用程序的入口点。
//
#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <WinSock2.h>
#include <process.h>

#pragma comment(lib, "Ws2_32.lib")
#define BUF_SIZE 2048
#define BUF_SMALL 100
/*typedef struct REQUEST
{
HANDLE hExiti;
SOCKET Socket;
int nMethod;
DWORD dwRecv;
DWORD deSend;
HANDLE hFile;
char szFileName[_MAX_PATH];
char postfix[10];
char StatuCodeReason[100];
void *pHttpProtocol;
}REQUEST,*PREQUEST;*/

//Functions
/*bool CHttpProtocol::StartHttpSrv()
{
WORD wVersionRequested;
WSADATA wsaData;
WSAStartup(wVersionRequested, &wsaData);
}*/
unsigned WINAPI RequestHandler(void *arg);
const char* ContentType(char *file);
void SendData(SOCKET sock, char *ct, char *fileName);
void SendErrorMSG(SOCKET sock);
void ErrorHandling(const char *message);

int main(int argc, char *argv[])
{
	WSADATA wsaData;
	SOCKET hServSock, hClntSock;
	//typedef _W64 unsigned int UINT_PTR，typedef UINT_PTR SOCKET_w64，
	// _W64用于指针运算。在32位编译环境占4个字节，在64位编译环境占8个字节。
	SOCKADDR_IN servAdr, clntAdr;
	HANDLE hThread;
	DWORD dwThreadID;
	int clnAdrSize;

	if (argc != 2)
	{
		printf("Usage:%s<port>\n", argv[0]);
		getchar();
		exit(1);
	}

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)//异步套接字是否正常启动
		ErrorHandling("WSAStartup() error!");
	hServSock = socket(PF_INET, SOCK_STREAM, 0);
	memset(&servAdr, 0, sizeof(servAdr));
	servAdr.sin_family = AF_INET;
	servAdr.sin_addr.s_addr = htonl(INADDR_ANY);//servAdr.sin_addr.sin_addr = htonl(INADDR_ANY);
	servAdr.sin_port = htons(atoi(argv[1]));
	if (bind(hServSock, (SOCKADDR*)&servAdr, sizeof(servAdr)) == SOCKET_ERROR)
		ErrorHandling("bind() error");

	while (1)
	{
		clnAdrSize = sizeof(clntAdr);
		hClntSock = accept(hServSock, (SOCKADDR*)&clntAdr, &clnAdrSize);
		printf("Connection Request:%s:%d\n", inet_ntoa(clntAdr.sin_addr), ntohs(clntAdr.sin_port));
		hThread = (HANDLE)_beginthreadex(NULL, 0, RequestHandler, (void*)hClntSock, 0, (unsigned*)&dwThreadID);
	}
	closesocket(hServSock);
	WSACleanup();
	system("pause");
	return 0;
}
/**************************************/
unsigned WINAPI RequestHandler(void *arg)
{
	SOCKET hClntSock = (SOCKET)arg;
	char buf[BUF_SIZE];
	char method[BUF_SMALL];
	char ct[BUF_SMALL];
	char fileName[BUF_SMALL];
	recv(hClntSock, buf, BUF_SIZE, 0);
	if (strstr(buf, "HTTP/") == NULL)
	{
		SendErrorMSG(hClntSock);
		closesocket(hClntSock);
		getchar();
		return 1;
	}
	strcpy(method, strtok(buf, "/"));
	if (strcmp(method, "GET"))
		SendErrorMSG(hClntSock);
	strcpy(fileName, strtok(NULL, "/"));
	strcpy(ct, ContentType(fileName));
	SendData(hClntSock, ct, fileName);
	getchar();
	return 0;
}

void SendData(SOCKET sock, char *ct, char *fileName)
{
	char protocol[] = "HTTP/1.0 200 OK\r\n";
	char servName[] = "Server:simple web server\r\n";
	char cntLen[] = "Content-legth:2048\r\n";
	char cntType[BUF_SMALL];
	char buf[BUF_SIZE];
	FILE *sendFile;
	sprintf(cntType, "Content-tyoe:%s\r\n\r\n", ct);
	if ((sendFile = fopen(fileName, "r")) == NULL)
	{
		SendErrorMSG(sock);
		getchar();
		return;
	}
	send(sock, protocol, strlen(protocol), 0);
	send(sock, servName, strlen(servName), 0);
	send(sock, cntLen, strlen(cntLen), 0);
	send(sock, cntType, strlen(cntType), 0);
	while (fgets(buf, BUF_SIZE, sendFile) != NULL)
		send(sock, buf, strlen(buf), 0);
	closesocket(sock);
	getchar();
	return;
}

void SendErrorMSG(SOCKET sock)
{
	char protocol[] = "HTTP/1.0 400 BadRequest\r\n";
	char servName[] = "Server:simple web server\r\n";
	char cntLen[] = "Content-length:2048\r\n";
	char cntType[] = "Content-type:text/html\r\n\r\n";
	char content[] = "<html><head><title>NETWORK</title></head>""<body><font size=+5><br>Error！查看请求文件名和请求方式！""</font></body><html>";
	send(sock, protocol, strlen(protocol), 0);
	send(sock, servName, strlen(servName), 0);
	send(sock, cntLen, strlen(cntLen), 0);
	send(sock, cntType, strlen(cntType), 0);
	send(sock, content, strlen(content), 0);
	closesocket(sock);
	getchar();
	return;
}

const char* ContentType(char *file)
{
	char extension[BUF_SMALL];
	char fileName[BUF_SMALL];
	strcpy(fileName, file);
	strtok(fileName, ".");
	strcpy(extension, strtok(NULL, ","));
	if (!strcmp(extension, "html") || !strcmp(extension, "htm"))
		return "text/html";
	else
		return"text/plain";
}

void ErrorHandling(const char *message)
{
	fputs(message, stderr);
	fputc('\n', stderr);
	getchar();
	exit(1);
}
//黄书中main函数最前几行
/*int m_listenSocket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0,WSA_FLAG_OVERLAPPED);
bind(m_listenSocket, (LPSOCKADDR)&sockAddr, sizeof(strhck sockaddr));
listen(m_listenSocket, SOMAXCONN);
m_pListenThread = AfxBeginThread(ListenThread, this);*/