// testSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <WinSock2.h>
#include<ctime>
#pragma comment(lib,"ws2_32.lib")
#define PORT 9000
#define IP "127.0.0.1"

SOCKET client;
SOCKET thisRecv;
SOCKADDR_IN serveraddr;
SOCKADDR_IN thisaddr;
WSADATA wsa;

DWORD WINAPI ReceiverThread(LPVOID);

int main()
{
	WSAStartup(MAKEWORD(2, 2), &wsa);
	client = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	thisRecv = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	thisaddr.sin_addr.s_addr = htonl(ADDR_ANY);
	thisaddr.sin_family = AF_INET;
	thisaddr.sin_port = htons(PORT);
	bind(thisRecv, (SOCKADDR *)&thisaddr, sizeof(thisaddr));
	listen(thisRecv, 5);
	

	/*serveraddr.sin_addr.s_addr = htonl(atoi(IP));
	serveraddr.sin_family = AF_INET;
	serveraddr.sin_port = htons(PORT);
	connect(client, (SOCKADDR *)&serveraddr, sizeof(serveraddr));*/

	sf::RenderWindow window(sf::VideoMode(0, 0, 0), "Recording sound...");
	sf::Event e;
	sf::Sound sound;
	sf::SoundBuffer soundBuffer;
	sf::SoundBufferRecorder soundBufferRecorder;

	time_t current_time = time(NULL);
	soundBufferRecorder.start(44100);
	char buff_read_mp3[1024];
	int ret;

	CreateThread(0, 0, ReceiverThread, &thisRecv, 0, 0);
}
DWORD WINAPI ReceiverThread(LPVOID lpParam) {
	//***new thread to recv data from server

	SOCKET recver = *(SOCKET *)lpParam;
	char buff_recv[1024];
	int ret;

	while (true) {
		ret = recv(recver, buff_recv, sizeof(buff_recv), 0);
		printf("%d: %s\n", ret, buff_recv);

	}

}

