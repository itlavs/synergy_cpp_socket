// Socket.cpp: Http сервер на сокетах.

// Виды нотаций:
// WsaData - паскалевская нотация (Microsoft)
// wsaData - верблюжья нотация (Oracle)
// wsa_data - змеиная нотация (Python)
// wsa-data - кебаб нотация

// Если проблемы со сборкой в Visual Studio 2012:
// Проект -> Свойства: Socket... ->
// Свойства конфигурации -> Компоновщик -> Все параметры -> Дополнительные зависимости -> Изменить
// Вставить в пустое поле: wsock32.lib

#include "stdafx.h"
#include "winsock.h"

SOCKET serversocket;
SOCKET clientsocket;
SOCKADDR_IN socketaddress;

// Подключение к сокетам
void StartWinSock()
{
	WSADATA WsaData;
	if (WSAStartup(0x0101, &WsaData) == SOCKET_ERROR)
	{
		printf("WSAStartup() error: %ld\n", GetLastError());	
	}
	else 
	{
		printf("Winsock init OK\n");
	}
}

// Получение имени машины
void GetHostName()
{
	char chInfo[64];

	if (gethostname(chInfo, sizeof(chInfo)))
	{
		printf("Not local host\n");
	}
	else
	{
		printf("Hostname: %s OK\n", chInfo);
	}
}

// Очистка сокетов
void CleanWinSock()
{
	closesocket(serversocket);
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

// Создание сокета
void CreateSocket()
{
	serversocket = socket(AF_INET, SOCK_STREAM, 0);
	if (serversocket == INVALID_SOCKET)
	{
		printf("Error on create socket\n");
		exit(1);
	}
	else
	{
		printf("Socket OK\n");
	}
}

// Связывание сокета с адресами
void BindSocket()
{
	socketaddress.sin_family = AF_INET;
	socketaddress.sin_addr.s_addr = INADDR_ANY;
	socketaddress.sin_port = htons(8080);
	int reuse = 1;

	if (setsockopt(serversocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&reuse, sizeof(reuse)))
	{
		printf("Set sock opt\n");
	}
	else
	{
		printf("Set sock opt OK\n");
	}
	if (bind(serversocket, (LPSOCKADDR)&socketaddress, sizeof(socketaddress)) == SOCKET_ERROR)
	{
		printf("Error bind socket\n");
	}
	else
	{
		printf("Bind socket OK\n");
	}
}

// Ожидание входящих запросов
void WaitSocket()
{
	#define QUEUE_SIZE 5
	if (listen(serversocket, QUEUE_SIZE) == SOCKET_ERROR)
	{
		printf("Error listen socket\n");
	}
	else
	{
		printf("Wait for connection ... ");
	}
}

// Отправляем данные клиенту 
void SendData(LPSTR buff)
{
	if (send(clientsocket, (LPSTR) buff, strlen(buff), 0) == SOCKET_ERROR) 
	{
		printf("Error send data\n");
	}
	else
	{
		printf("Send: ");
		printf(buff);
		printf(" OK\n");
	}
}

// Соединение клиента и сервера установлено
void ServerAccept()
{
	int length = sizeof(socketaddress);
	clientsocket = accept(serversocket, (LPSOCKADDR)&socketaddress, &length);
	if (clientsocket == INVALID_SOCKET)
	{
		printf("OK\n");
		printf("Invalid client socket\n");
		return;
	}
	else
	{
		printf("OK\n");
		printf("Accept client socket OK\n");
	}
	LPSTR buff = "HTTP/1.1 200 OK\r\nContent-Length: 58\r\nContent-type: text/html\r\n\r\n<html><head></head><body><p>Hello world!</p></body></html>";
	SendData(buff);
	closesocket(clientsocket);
}


void _tmain(int argc, _TCHAR* argv[])
{
	StartWinSock();
	GetHostName();
	CreateSocket();
	BindSocket();
	WaitSocket();
	ServerAccept();
	CleanWinSock();
}

