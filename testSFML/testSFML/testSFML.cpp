// testSFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <ctime>

#include <iostream>
#include <chrono>
#include <thread>
#include <functional>
sf::RenderWindow window(sf::VideoMode(0, 0, 0), "Recording sound...");
sf::Event e;
sf::Sound sound;
sf::SoundBuffer soundBuffer;
sf::SoundBufferRecorder soundBufferRecorder;

void timer_start(std::function<void(void)> func, unsigned int interval)
{
	std::thread([func, interval]() {
		while (true)
		{
			func();
			std::this_thread::sleep_for(std::chrono::milliseconds(interval));
		}
	}).detach();
}

void record() {
	printf("save\n");
	soundBufferRecorder.stop();
	soundBuffer = soundBufferRecorder.getBuffer();
	soundBuffer.saveToFile("test.wav");
	system("lame.exe test.wav test.mp3");
	sound.setBuffer(soundBuffer);
	sound.play();

	char buff[1024];

	FILE *f = fopen("test.mp3", "rb");
	int ret;
	while ((ret = fread(buff, 1, sizeof(buff), f) > 0)) {
		printf(buff);
	}
	fclose(f);
}

int main()
{

	//timer_start(record, 3000);

	//time_t start,now;
	//Zint start = time(NULL);


	//while (true) {
		//printf("recording........%d-%d\n",cur,time(NULL));
		/*time(&now);
		printf("recording........%s\n", difftime(now,start));
		printf("%d %d\n", now, start);
		if (difftime(start, time(NULL)) > 2) {
			printf("save\n");
			soundBufferRecorder.stop();
			soundBuffer = soundBufferRecorder.getBuffer();
			soundBuffer.saveToFile("test.wav");
			system("lame.exe test.wav test.mp3");
			sound.setBuffer(soundBuffer);
			sound.play();

			char buff[1024];

			FILE *f = fopen("test.mp3", "rb");
			int ret;
			while ((ret = fread(buff, 1, sizeof(buff), f) > 0)) {
				printf(buff);
			}
			fclose(f);
			start = time(NULL);
		}*/
		
	//}
	while (true) {
		while (window.pollEvent(e)) {
			switch (e.type)
			{
			case sf::Event::KeyPressed :
			{
				if (e.key.code == sf::Keyboard::Space) {
					soundBufferRecorder.start(44100);
				}else
				if (e.key.code == sf::Keyboard::Enter) {
					soundBufferRecorder.stop();
					soundBuffer = soundBufferRecorder.getBuffer();
					soundBuffer.saveToFile("test.wav");
					system("lame.exe test.wav test.mp3");
					sound.setBuffer(soundBuffer);
					sound.play();

					char buff[1024];

					FILE *f = fopen("test.mp3", "rb");
					int ret;
					while((ret=fread(buff,1,sizeof(buff),f)>0)){
						printf(buff);
					}
					fclose(f);
				}
			}
			
			}
		}
	}
}

