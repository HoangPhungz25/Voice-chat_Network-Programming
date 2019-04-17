
#include "stdafx.h"
#include<stdio.h>
#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<WS2tcpip.h>
#define PORT 9000
#define LOCAL_IP_ADDR "127.0.0.1"
int main() {

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN server;
	server.sin_addr.s_addr = inet_addr(LOCAL_IP_ADDR);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	while (true) {
		connect(client, (SOCKADDR *)&server, sizeof(server));
	}
}