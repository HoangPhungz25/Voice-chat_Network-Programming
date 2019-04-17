#include "pch.h"
#include <iostream>
#include <winsock2.h>
#include <stdio.h>
#pragma comment(lib, "ws2_32.lib")
#define PORT  88
#define IP  ADDR_ANY
#define MAX_SIZE_OF_BUFF 1024

WSADATA wsa;
fd_set fdRead;
SOCKET server;
SOCKADDR_IN serveraddr;

struct _info {
	char username[256];
	char password[256];
} infors[64];

int numInfors = 0;

struct _client {
	SOCKET socket;
	char username[256];
	char password[256];
	bool isLoggedIn = false;
} clients[64];
int numClients = 0;

timeval tv;

bool checkAccountInfor(char[], _client*);
void sendMsgToAllOtherClients(char[], char[]);

int main()
{
	tv.tv_sec = 1;

	WSAStartup(MAKEWORD(2, 2), &wsa);
	server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	serveraddr.sin_addr.s_addr = htonl(IP);
	serveraddr.sin_port = htons(PORT);
	serveraddr.sin_family = AF_INET;

	bind(server, (SOCKADDR *)&serveraddr, sizeof(serveraddr));
	listen(server, 5);

	int ret;
	char buff_recv[1024];
	const char *msg_login_succ = "Login successfully!\n";
	const char *msg_login = "Pls login!\n";
	const char *msg_wrong_info = "Wrong info, pls re-login!\n";

	while (true) {

		FD_ZERO(&fdRead);
		FD_SET(server, &fdRead);
		for (int i = 0; i < numClients; i++) {
			FD_SET(clients[i].socket, &fdRead);
		}
		
		if ((ret = select(0, &fdRead, NULL, NULL, &tv)) == SOCKET_ERROR) {
			printf("error: %d", WSAGetLastError());
			continue;
		}

		if (ret > 0) {
			if (FD_ISSET(server, &fdRead)) {
				SOCKET pendingClient = accept(server, NULL, NULL);
				if (pendingClient != INVALID_SOCKET) {
					FD_SET(pendingClient, &fdRead);
					printf("Connect repest from Client : %d", pendingClient);
					clients[numClients].socket = pendingClient;
					numClients++;
				}
				else {
					printf("Conecting Error: %d", WSAGetLastError());
				}
			}
			
			for (int i = 0; i < numClients; i++) {
				if (FD_ISSET(clients[i].socket, &fdRead)) {
					ret = recv(clients[i].socket, buff_recv, sizeof(buff_recv),0);

					//cut buff
					if (ret < 0) {
						continue;
					}
					if (ret > MAX_SIZE_OF_BUFF) {
						buff_recv[MAX_SIZE_OF_BUFF-1] = 0;
					}
					else {
						buff_recv[ret] = 0;
					}

					//check if logged in or chating
					if (clients[i].isLoggedIn) {
						sendMsgToAllOtherClients(clients[i].username, buff_recv);
					}
					else {
						printf("%s\n", buff_recv);
						if (checkAccountInfor(buff_recv, &clients[i])) {
							send(clients[i].socket, msg_login_succ, strlen(msg_login_succ),0);
						}
						else {
							send(clients[i].socket, msg_wrong_info, strlen(msg_wrong_info), 0);
						}
					}
				}
			}
		}

	}

	WSACleanup();
}

void sendMsgToAllOtherClients(char username[], char buff[]) {
	char buff_sprint[1024];
	sprintf(buff_sprint, "%s : %s", username, buff);
	for (int i = 0; i < numClients; i++) {
		send(clients[i].socket, buff_sprint, strlen(buff_sprint), 0);
	}

}
bool checkAccountInfor(char buff[], _client* client) {
	char s1[256], s2[256];
	sscanf(buff, "%s %s", s1, s2);
	bool matched = false;
	for (int i = 0; i < numInfors; i++) 
		if (strcmp(s1, infors[i].username) && strcmp(s2, infors[i].password)) {
			matched = true;
			break;
		}
	
	if(matched){
		strcpy(client->username,s1);
		strcpy(client->password, s2);
		client->isLoggedIn = true;
		return true;
	}
	return false;
}