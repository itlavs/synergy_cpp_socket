// Socket.cpp: определяет точку входа для консольного приложения.
//
// WsaData - паскалевская нотация (Microsoft)
// wsaData - верблюжья нотация (Oracle)
// wsa_data - змеиная нотация (Python)
// wsa-data - кебаб нотация
// wsock32.lib

#include "stdafx.h"
#include "winsock.h"

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA WsaData;
	char chInfo[64];

	// Подключение к сокетам
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

	// Получение имени машины
	if (gethostname(chInfo, sizeof(chInfo)))
	{
		printf("Not local host\n");
	}
	else
	{
		printf("Hostname: %s\n", chInfo);
	}

	// Очистка
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

