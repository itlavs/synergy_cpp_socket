// Socket.cpp: ���������� ����� ����� ��� ����������� ����������.
//
// WsaData - ������������ ������� (Microsoft)
// wsaData - ��������� ������� (Oracle)
// wsa_data - ������� ������� (Python)
// wsa-data - ����� �������
// wsock32.lib

#include "stdafx.h"
#include "winsock.h"

WSADATA WsaData;
SOCKET servsocket;

// ����������� � �������
int StartWinSock()
{
	int err = WSAStartup(0x0101, &WsaData);
	if (err == SOCKET_ERROR)
	{
		printf("WSAStartup() error: %ld\n", GetLastError());
		return 1;	
	}
	else 
	{
		printf("Winsock init OK\n");
		return 0;
	}
}

// ��������� ����� ������
void GetHostName()
{
	char chInfo[64];

	if (gethostname(chInfo, sizeof(chInfo)))
	{
		printf("Not local host\n");
	}
	else
	{
		printf("Hostname: %s\n", chInfo);
	}
}

// ������� �������
void CleanWinSock()
{
	if (WSACleanup())
	{
		printf("Error cleanup\n");
	}
	else
	{
		printf("Cleanup OK\n");
	}
	system("pause");
}

// �������� ������
void CreateSocket()
{
	servsocket = socket(PF_INET, SOCK_STREAM, 0);
	if (servsocket == INVALID_SOCKET)
	{
		printf("Error on create socket\n");
		exit(1);
	}
	else
	{
		printf("Socket OK\n");
	}
}

void BindSocket()
{
	SOCKADDR_IN socketaddress;
	socketaddress.sin_family = AF_INET;
	socketaddress.sin_addr.s_addr = INADDR_ANY;
	socketaddress.sin_port = 80;

	if (bind(servsocket, (LPSOCKADDR)&socketaddress, sizeof(socketaddress)) == SOCKET_ERROR)
	{
		printf("Error bind socket\n");
		//exit(1);
	}
	else
	{
		printf("Bind socket OK\n");
	}
}

void WaitSocket()
{
	#define QUEUE_SIZE 5
	if (listen(servsocket, QUEUE_SIZE) == SOCKET_ERROR)
	{
		printf("Error listen socket\n");
		//exit(1);
	}
	else
	{
		printf("Wait for connection\n");
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	if (StartWinSock())
	{
		return 1;
	}
	GetHostName();
	CreateSocket();
	BindSocket();
	WaitSocket();
	closesocket(servsocket);
	CleanWinSock();

	return 0;
}

