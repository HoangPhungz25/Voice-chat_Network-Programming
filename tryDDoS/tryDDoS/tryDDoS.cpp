// tryDDoS.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma comment(lib,"ws2_32.lib")
#include<winsock2.h>
#include<WS2tcpip.h>
#define PORT 9000
#define LOCAL_IP_ADDR "127.0.0.1"
int main() {

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);
	SOCKET client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//SOCKET client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN server;
	server.sin_addr.s_addr = inet_addr(LOCAL_IP_ADDR);
	server.sin_port = htons(PORT);
	server.sin_family = AF_INET;

	connect(client, (SOCKADDR *)&server, sizeof(server));
	const char *msg = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n";
	char msg_send[1024];
	sprintf(msg_send, "%d : %s",client, msg);
	while (true) {
		send(client, msg_send, strlen(msg_send),0);
		Sleep(3);
	}
}