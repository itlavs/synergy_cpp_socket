// Socket.cpp: ���������� ����� ����� ��� ����������� ����������.
//
// WsaData - ������������ ������� (Microsoft)
// wsaData - ��������� ������� (Oracle)
// wsa_data - ������� ������� (Python)
// wsa-data - ����� �������
// wsock32.lib

#include "stdafx.h"
#include "winsock.h"

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA WsaData;
	char chInfo[64];

	// ����������� � �������
	int err = WSAStartup(0x0101, &WsaData);
	if (err == SOCKET_ERROR)
	{
		printf("WSAStartup() error: %ld\n", GetLastError());
		return 1;	
	}
	else 
	{
		printf("Winsock init OK\n");
	}

	// ��������� ����� ������
	if (gethostname(chInfo, sizeof(chInfo)))
	{
		printf("Not local host\n");
	}
	else
	{
		printf("Hostname: %s\n", chInfo);
	}

	// �������
	if (WSACleanup())
	{
		printf("Error cleanup\n");
	}
	else
	{
		printf("Cleanup OK\n");
	}
	system("pause");
	return 0;
}

