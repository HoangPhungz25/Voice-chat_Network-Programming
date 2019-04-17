
#include "pch.h"
#include <iostream>
#include <WinSock2.h>
#pragma comment(lib,"ws2_32.lib")
#define IP_ADDR ADDR_ANY
#define PORT 88

int main()
{

	WSADATA wsa;
	WSAStartup(MAKEWORD(2, 2), &wsa);

	SOCKET server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	SOCKADDR_IN server_addr;
	server_addr.sin_addr.s_addr = htonl(IP_ADDR);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(PORT);

	bind(server, (SOCKADDR *)&server_addr, sizeof(server_addr));
	listen(server, 10);



	
	OVERLAPPED overlapped;
	WSAEVENT event = WSACreateEvent();
	memset(&overlapped, 0, sizeof(overlapped));
	overlapped.hEvent = event;

	char buffer[1024];
	WSABUF wsaBuf;
	wsaBuf.buf = buffer;
	wsaBuf.len = 1024;
	DWORD numberOfByteRecved = 0;
	DWORD flag = 0;

	
	int rc;
	char recvBuff[1024];
	while (true) {
		rc = WSARecv(server, &wsaBuf, 1, &numberOfByteRecved, &flag, &overlapped, 0);
		if (rc == SOCKET_ERROR) {
			rc =  WSAGetLastError();
			if (rc != WSA_IO_PENDING) {
				printf("error: %d", WSAGetLastError());
				continue;
			}
			
		}
		rc = WSAWaitForMultipleEvents(1, &event, TRUE, INFINITY, FALSE);
		if (rc == WSA_WAIT_FAILED || rc == WSA_WAIT_TIMEOUT) {
			continue;
		}
		ResetEvent(event);

		if (WSAGetOverlappedResult(server, &overlapped, &numberOfByteRecved, FALSE, 0)) {
			recvBuff[numberOfByteRecved] = 0;
			printf("%s",recvBuff);
		}
	}
   
}
