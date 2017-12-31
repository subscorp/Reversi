
#pragma once
#define BUFFER_SIZE 1024

#include <vector> //new
#include <string> // new
#include <map> // new
//#include <pair>
#include <pthread.h>
#include <thread>

#include "CommandsManager.h"

using namespace std; // new


class ReversiServer
{

public:
	ReversiServer(int port);
	void start();
	void stop();
	void *loopThread(void *arg);
	map<string, int > games;
	CommandsManager commandsManager;
	vector<pthread_t> threads;

private:
	int port;
	int serverSocket; // the socket's file descriptor

	int handleClient(int clientSocket, int clientSocket2);
};

