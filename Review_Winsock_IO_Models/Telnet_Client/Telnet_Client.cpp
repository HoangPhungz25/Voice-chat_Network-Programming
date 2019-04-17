#include "pch.h"
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT  88
#define IP  "127.0.0.1"
#define MAX_SIZE_OF_BUFF 1024

WSADATA wsa;
SOCKET client;
SOCKADDR_IN server;
fd_set fdRead;

int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	server.sin_addr.s_addr = inet_addr(IP);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	connect(client, (SOCKADDR *)&server, sizeof(server));
	int num = 0;
	char buff[1024], buff_recv[1024];
	int ret;
	while (true) {
		gets_s(buff);
		send(client, buff, strlen(buff), 0);

		FD_ZERO(&fdRead);
		FD_SET(client, &fdRead);
		ret = select(0, &fdRead, NULL, NULL, NULL);
		if (ret != SOCKET_ERROR) {
			ret = recv(client, buff_recv, sizeof(buff_recv), 0);
			if (ret > 0 && ret < 1024) {
				buff_recv[ret] = 0;
				printf("%s\n", buff_recv);
			}
		}

		
	}	
	WSACleanup();
}

