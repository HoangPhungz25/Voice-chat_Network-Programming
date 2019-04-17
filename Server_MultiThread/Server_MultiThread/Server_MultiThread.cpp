#include "pch.h"
#pragma comment(lib,"ws2_32.lib")
#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<winsock2.h>
#include<WS2tcpip.h>
#include <iostream>
#define PORT 9000
#define IP_ADDR ADDR_ANY

DWORD WINAPI ListenerThread(LPVOID);
SOCKET clients[100];
int numClients = 0;


int main()
{
	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN server_addr;
	server_addr.sin_addr.s_addr =htonl(IP_ADDR);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	bind(server, (SOCKADDR *)&server_addr, sizeof(server_addr));
	listen(server, 10);
	while (true) {
		SOCKET newClient = accept(server, NULL, NULL);
		if (newClient != INVALID_SOCKET) {
			CreateThread(0, 0, ListenerThread, &newClient, 0, 0);
		}
	}

	WSACleanup();
}
DWORD WINAPI ListenerThread(LPVOID lpParam) {
	SOCKET newClient = *(SOCKET*)lpParam;
	clients[numClients] = newClient;
	numClients++;

	char buff_recv[1024];
	int ret;
	while (true) {
		ret = recv(newClient, buff_recv, sizeof(buff_recv), 0);
		if(ret>0 && ret<1024) buff_recv[ret] = 0;
		else if (ret < 0) continue;
		else buff_recv[1023] = 0;
		printf("%d : %s", newClient, buff_recv);
	}

}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
